#include "gtest/gtest.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/Zip/ZipStream.h"
#include "Poco/Zip/Compress.h"
#include "Poco/Zip/Decompress.h"
#include "Poco/StreamCopier.h"
#include "Poco/Delegate.h"

#include <sstream>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

class ZipTestSuite: public testing::Test {
public:
    static void SetUpTestCase(){
    }

    static void TearDownTestCase(){
    }

    static std::string getTestFile(std::string const& directory, std::string const& file) {
        std::stringstream ostr;
        ostr << directory << "/" << file;
        std::string validDir(ostr.str());
        Poco::Path pathPattern(validDir);
        // If the file exists, then return the file path directly
        if(Poco::File(pathPattern).exists()) {
            return validDir;
        }
        return "";
    }
};

TEST_F(ZipTestSuite, TestZipSingleFile) {
    Poco::FileOutputStream out(Poco::Path::current() + "appinf.zip");
    Poco::Path theFile(getTestFile("data", "1.txt"));
    Poco::Zip::Compress c(out, true);
    c.addFile(theFile, theFile.getFileName());
    Poco::Zip::ZipArchive a(c.close());
}


TEST_F(ZipTestSuite, TestDirectory) {
    Poco::FileOutputStream out(Poco::Path::current() + "pocobin.zip");
    Poco::File aFile("some/");
    if(aFile.exists()) aFile.remove(true);

    Poco::File aDir("some/recursive/dir/");
    aDir.createDirectories();
    Poco::File aDir2("some/other/recursive/dir/");
    aDir2.createDirectories();
    Poco::File aF("some/recursive/dir/test.file");
    aF.createFile();
    Poco::FileOutputStream fos(aF.path());
    fos << "Just some test data";
    fos.close();

    Poco::Path theFile(aFile.path());
    // Create zip dir in the zip file, not an actual directory
    theFile.makeDirectory();
    Poco::Zip::Compress c(out, true);
    c.addRecursive(theFile, Poco::Zip::ZipCommon::CL_MAXIMUM, false, theFile);
    Poco::Zip::ZipArchive a(c.close());
    Poco::File(aFile).remove(true);
}

TEST_F(ZipTestSuite, TestDecompressSingleFile) {
    std::string testFile = getTestFile(Poco::Path().current(), "appinf.zip");
    Poco::FileInputStream inp(testFile);
    ASSERT_TRUE(inp.good());
    Poco::Zip::ZipArchive arch(inp);
    Poco::Zip::ZipArchive::FileHeaders::const_iterator it = arch.findHeader("1.txt");
    ASSERT_TRUE(it != arch.headerEnd());
    Poco::Zip::ZipInputStream zipin(inp, it->second);
    std::ostringstream out(std::ios::binary);
    Poco::StreamCopier::copyStream(zipin, out);
    std::cout << out.str() << std::endl;
    ASSERT_TRUE(!out.str().empty());
}

TEST_F(ZipTestSuite, TestDecompressSingleFileInDir) {
    std::string testFile = getTestFile(Poco::Path().current(), "pocobin.zip");
    Poco::FileInputStream inp(testFile);
    ASSERT_TRUE(inp.good());
    Poco::Zip::ZipArchive arch(inp);
    Poco::Zip::ZipArchive::FileHeaders::const_iterator it = arch.findHeader("some/recursive/dir/test.file");
    ASSERT_TRUE(it != arch.headerEnd());
    Poco::Zip::ZipInputStream zipin(inp, it->second);
    std::ostringstream out(std::ios::binary);
    Poco::StreamCopier::copyStream(zipin, out);
    std::cout << out.str() << std::endl;
    ASSERT_TRUE(!out.str().empty());
}

struct DecompressErrHandler {
    int _err_cnt{0};
    void onDecompressError(const void* pSender, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string>& info){
        ++_err_cnt;
    }
};

TEST_F(ZipTestSuite, TestDecompressAllFiles) {
    std::string testFile = getTestFile(Poco::Path().current(), "pocobin.zip");
	Poco::FileInputStream inp(testFile);
	ASSERT_TRUE(inp.good());
	Poco::Zip::Decompress dec(inp, Poco::Path::current());
    int err_Cnt = 0;
    auto onDecompressError = [&err_Cnt](const void* pSender, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string>& info) {
        ++err_Cnt;
    };
    DecompressErrHandler err_handler;
    dec.EError += Poco::Delegate<DecompressErrHandler, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string>>(&err_handler, &DecompressErrHandler::onDecompressError);
    dec.decompressAllFiles();
    dec.EError -= Poco::Delegate<DecompressErrHandler, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string>>(&err_handler, &DecompressErrHandler::onDecompressError);
    ASSERT_TRUE(err_handler._err_cnt == 0);
    ASSERT_TRUE(!dec.mapping().empty());
}

TEST_F(ZipTestSuite, TestDecompressAllFilesFlat) {
    std::string testFile = getTestFile(Poco::Path().current(), "pocobin.zip");
	Poco::FileInputStream inp(testFile);
	ASSERT_TRUE(inp.good());
    // The third parameter, flattenDirs=true
	Poco::Zip::Decompress dec(inp, Poco::Path::current(), true);
    int err_Cnt = 0;
    auto onDecompressError = [&err_Cnt](const void* pSender, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string>& info) {
        ++err_Cnt;
    };
    DecompressErrHandler err_handler;
    dec.EError += Poco::Delegate<DecompressErrHandler, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string>>(&err_handler, &DecompressErrHandler::onDecompressError);
    dec.decompressAllFiles();
    dec.EError -= Poco::Delegate<DecompressErrHandler, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string>>(&err_handler, &DecompressErrHandler::onDecompressError);
    ASSERT_TRUE(err_handler._err_cnt == 0);
    ASSERT_TRUE(!dec.mapping().empty());
}