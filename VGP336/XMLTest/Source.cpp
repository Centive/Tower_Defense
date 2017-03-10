#include <tinyxml.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

//2
void WriteDocFile()
{
	TiXmlDocument doc;
	TiXmlElement* msg;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement * root = new TiXmlElement("MyApp");
	doc.LinkEndChild(root);

	TiXmlComment * comment = new TiXmlComment();
	comment->SetValue(" Settings for MyApp ");
	root->LinkEndChild(comment);

	TiXmlElement * msgs = new TiXmlElement("Messages");
	root->LinkEndChild(msgs);

	msg = new TiXmlElement("Welcome");
	msg->LinkEndChild(new TiXmlText("Welcome to MyApp"));
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("Farewell");
	msg->LinkEndChild(new TiXmlText("Thank you for using MyApp"));
	msgs->LinkEndChild(msg);

	TiXmlElement * windows = new TiXmlElement("Windows");
	root->LinkEndChild(windows);

	TiXmlElement * window;
	window = new TiXmlElement("Window");
	windows->LinkEndChild(window);
	window->SetAttribute("name", "MainFrame");
	window->SetAttribute("x", 5);
	window->SetAttribute("y", 15);
	window->SetAttribute("w", 400);
	window->SetAttribute("h", 250);

	TiXmlElement * cxn = new TiXmlElement("Connection");
	root->LinkEndChild(cxn);
	cxn->SetAttribute("ip", "192.168.0.1");
	cxn->SetDoubleAttribute("timeout", 123.456);

	doc.SaveFile("appsettings.xml");
}

//1
void AddingAttributes()
{
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement * element = new TiXmlElement("Shape");
	doc.LinkEndChild(element);
	element->SetAttribute("name", "Circle");
	element->SetAttribute("x", 5);
	element->SetAttribute("y", 15);
	element->SetDoubleAttribute("radius", 3.14159);
	TiXmlText * text = new TiXmlText("World");
	element->LinkEndChild(text);
	doc.SaveFile("myXML.xml");
}
/*
void dump_to_stdout(const char* pFilename)
{
	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		printf("\n%s:\n", pFilename);
		dump_to_stdout(&doc); // defined later in the tutorial
	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
	}
}
*/
void main()
{
	TiXmlDocument doc("../Data/template/CompleteCamera.xml");

	if (!doc.LoadFile())
	{
		return;
	}

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem = hDoc.FirstChild().Element();
	if (!pElem)
	{
		return;
	}

	hRoot = TiXmlHandle(pElem);

	if ((string)pElem->Value() == "GameObjects")
	{
		//iterate through the game objects
		for (TiXmlElement* pTemp1 = TiXmlHandle(pElem).FirstChild().Element(); 
			pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//found a gameobject!
			if ((string)pTemp1->Value() == "GameObject")
			{
				string kname;//
				string ktemplate;//

				TiXmlElement* pTemp2 = TiXmlHandle(pTemp1).FirstChild().Element();

				//Get the NAME of the gameobject and TEMPLATE
				kname = pTemp2->GetText();
				pTemp2 = pTemp2->NextSiblingElement();
				ktemplate = pTemp2->GetText();
				//

				//Check if the gameobject is given a transform
				pTemp2 = pTemp2->NextSiblingElement();
				if (pTemp2)
				{
					std::string pName = pTemp2->Attribute("name");
					if (pName == "Position")
					{
						float pos[3];//
						pTemp2 = pTemp2->NextSiblingElement();
						pTemp2->Value();

						for (int i = 0; i < 3; pTemp2 = pTemp2->NextSiblingElement(), i++)
						{
							pos[i] = strtof(pTemp2->GetText(), 0);
						}

					}
				}
				//
			}
		}
	}
	getchar();
}