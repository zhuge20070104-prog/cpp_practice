#include "gtest/gtest.h"

#include "Poco/SAX/SAXParser.h"
#include "Poco/SAX/ContentHandler.h"
#include "Poco/SAX/LexicalHandler.h"
#include "Poco/SAX/Attributes.h"
#include "Poco/SAX/Locator.h"
#include "Poco/Exception.h"

#include <iostream>
#include <map>


using Poco::XML::SAXParser;
using Poco::XML::XMLReader;
using Poco::XML::XMLString;
using Poco::XML::XMLChar;
using Poco::XML::ContentHandler;
using Poco::XML::LexicalHandler;
using Poco::XML::Attributes;
using Poco::XML::Locator;


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

class MyXMLHandler: public ContentHandler, public LexicalHandler {
public:
	MyXMLHandler():
		_pLocator(0)
	{
	}

	// ContentHandler
	void setDocumentLocator(const Locator* loc)
	{
		_pLocator = loc;
	}

	void startDocument(){
	}

	void endDocument(){
	}

	void startElement(const XMLString& uri, const XMLString& localName, const XMLString& qname, const Attributes& attributes)
	{
		
        cur_local_name = localName;
        // Parse version from ivy-module node
        if(localName == "ivy-module") {
            for (int i = 0; i < attributes.getLength(); ++i){
                if(attributes.getLocalName(i) == "version") {
                    parsed_values.insert({attributes.getLocalName(i), attributes.getValue(i)});
                }
		    }
        }

        // Parse all attributes in info node
        if(localName == "info") {
            for (int i = 0; i < attributes.getLength(); ++i){
                parsed_values.insert({attributes.getLocalName(i), attributes.getValue(i)});
		    }
        }
	}

	void endElement(const XMLString& uri, const XMLString& localName, const XMLString& qname) {
	}

	void characters(const XMLChar ch[], int start, int length)
	{   
        // Insert description value
		if(cur_local_name == "description") {
            parsed_values.insert({"description", std::string(ch + start, length)});
        }
	}

	void ignorableWhitespace(const XMLChar ch[], int start, int length){
	}

    void processingInstruction(const XMLString& target, const XMLString& data){
	}

	void startPrefixMapping(const XMLString& prefix, const XMLString& uri){
	}

	void endPrefixMapping(const XMLString& prefix){
	}

	void skippedEntity(const XMLString& name){
	
	}

	// LexicalHandler
	void startDTD(const XMLString& name, const XMLString& publicId, const XMLString& systemId){
	}

	void endDTD(){
	}

	void startEntity(const XMLString& name){
	}

	void endEntity(const XMLString& name){
	}

    void startCDATA(){
	}

	void endCDATA(){
	}

	void comment(const XMLChar ch[], int start, int length){
	}

    std::map<std::string, std::string> get_parsed_values() {
        return parsed_values;
    }

protected:
	void where(const std::string& meth)
	{
		std::cout << "*** " << meth;
		if (_pLocator)
		{
			std::cout << " in "
			          << _pLocator->getSystemId()
			          << ", line " << _pLocator->getLineNumber()
			          << ", col " << _pLocator->getColumnNumber()
			          << std::endl;
		}
	}

private:
	const Locator* _pLocator;
    std::map<std::string, std::string> parsed_values; 
    std::string cur_local_name{""};

};


GTEST_TEST(SAXTestSuite, TestSax) {
   
    MyXMLHandler handler;

	SAXParser parser;
	parser.setFeature(XMLReader::FEATURE_NAMESPACES, true);
	parser.setFeature(XMLReader::FEATURE_NAMESPACE_PREFIXES, true);
	parser.setContentHandler(&handler);
	parser.setProperty(XMLReader::PROPERTY_LEXICAL_HANDLER, static_cast<LexicalHandler*>(&handler));

	try
	{
		parser.parse("./1.xml");
        auto parsed_values = handler.get_parsed_values();
        for(auto const& parsed_value: parsed_values) {
            std::cout << parsed_value.first << ": " << parsed_value.second << std::endl;
        }

        ASSERT_EQ("2.0", parsed_values["version"]);
        ASSERT_EQ("release", parsed_values["status"]);
        ASSERT_EQ("1.0.0-rc.1+23152204", parsed_values["revision"]);
        ASSERT_EQ("20210520075356", parsed_values["publication"]);
        ASSERT_EQ("telenav", parsed_values["organisation"]);
        ASSERT_EQ("PSD", parsed_values["module"]);
        std::string expected_desc = "Built from commit 7aa995ccbf1ad62052ad225b47dcd9ee8f7fd7a2, http://ec2d-jenkinsmaster-02.mypna.com:8080/job/TIPS-New/job/detection/job/release%252Fsprint10/2/";
        ASSERT_EQ(expected_desc, parsed_values["description"]);
	}
	catch (Poco::Exception& e)
	{
		std::cerr << e.displayText() << std::endl;
		ASSERT_TRUE(false);
	}
}


