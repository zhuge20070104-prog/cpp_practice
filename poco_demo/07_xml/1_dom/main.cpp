#include "gtest/gtest.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/Exception.h"
#include "Poco/XML/Name.h"

#include <iostream>
#include <fstream>

using Poco::XML::DOMParser;
using Poco::XML::InputSource;
using Poco::XML::Document;
using Poco::XML::NodeIterator;
using Poco::XML::NodeFilter;
using Poco::XML::Node;
using Poco::XML::AutoPtr;
using Poco::Exception;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}


GTEST_TEST(XMLDomTestSuite, TestDom) {
    std::ifstream ifs("./1.xml");
    if(!ifs) {
        std::cerr << "XML file doesn't exist!" << std::endl;
        ASSERT_TRUE(false);
    }

    InputSource src(ifs);
    try {
        DOMParser parser;
        AutoPtr<Document> pDoc = parser.parse(&src);
        NodeIterator it(pDoc, NodeFilter::SHOW_ALL);
        Node* pNode = it.nextNode();
        while(pNode) {
            if(pNode->nodeName() == "ivy-module") {
                std::string version = pNode->getNodeByPath("[@version]")->nodeValue();
                std::cout << "IVY module version: " << version << std::endl;
                ASSERT_EQ("2.0", version);
            }
            if(pNode->nodeName() == "info") {
                std::string organisation = pNode->getNodeByPath("[@organisation]")->nodeValue();
                std::string module = pNode->getNodeByPath("[@module]")->nodeValue();
                std::string revision = pNode->getNodeByPath("[@revision]")->nodeValue();
                std::string status = pNode->getNodeByPath("[@status]")->nodeValue();
                std::string publication = pNode->getNodeByPath("[@publication]")->nodeValue();
                std::cout << "organisation: " << organisation << std::endl;
                std::cout << "module: " << module << std::endl;
                std::cout << "revision: " << revision << std::endl;
                std::cout << "status: " << status << std::endl;
                std::cout << "publication: " << publication << std::endl;
                ASSERT_EQ("telenav", organisation);
                ASSERT_EQ("PSD", module);
                ASSERT_EQ("1.0.0-rc.1+23152204", revision);
                ASSERT_EQ("release", status);
                ASSERT_EQ("20210520075356", publication);
            } 
            if(pNode->nodeName() == "description") {
                std::string description = pNode->innerText();
                std::cout << "description: " << pNode->innerText() << std::endl;
                std::string expected_desc = "Built from commit 7aa995ccbf1ad62052ad225b47dcd9ee8f7fd7a2, http://ec2d-jenkinsmaster-02.mypna.com:8080/job/TIPS-New/job/detection/job/release%252Fsprint10/2/";
                ASSERT_EQ(expected_desc, description);
            }
            pNode = it.nextNode();
        }
    }catch(Exception const& ex) {
        std::cerr << ex.displayText() << std::endl;
        ifs.close();
        ASSERT_TRUE(false);
    }
    ifs.close();
}


