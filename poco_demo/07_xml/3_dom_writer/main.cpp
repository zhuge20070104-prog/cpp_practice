#include "gtest/gtest.h"

#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

#include <iostream>
#include <fstream>

using Poco::XML::Document;
using Poco::XML::Element;
using Poco::XML::Text;
using Poco::XML::AutoPtr;
using Poco::XML::DOMWriter;
using Poco::XML::XMLWriter;



int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

GTEST_TEST(DomTestSuite, TestDomWriter) {
	AutoPtr<Document> pDoc = new Document;

	AutoPtr<Element> pRoot = pDoc->createElement("root");
	pDoc->appendChild(pRoot);

	AutoPtr<Element> pChild1 = pDoc->createElement("child1");
	pChild1->setAttribute("child1Attr", "This is a attr for child1");

	AutoPtr<Text> pText1 = pDoc->createTextNode("text1");
	pChild1->appendChild(pText1);
	pRoot->appendChild(pChild1);

	AutoPtr<Element> pChild2 = pDoc->createElement("child2");
	AutoPtr<Text> pText2 = pDoc->createTextNode("text2");
	pChild2->appendChild(pText2);
	pChild2->setAttribute("child2Attr", "This is a attr for child2");
	pRoot->appendChild(pChild2);

	DOMWriter writer;
	writer.setNewLine("\n");
	writer.setOptions(XMLWriter::PRETTY_PRINT);
	writer.writeNode(std::cout, pDoc);
	std::ofstream ofs("1.xml", std::ios::out | std::ios::binary);
	
	writer.writeNode(ofs, pDoc);
	ofs.close();
}
