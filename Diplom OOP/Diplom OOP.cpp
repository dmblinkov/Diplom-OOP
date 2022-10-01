#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;




class Element
{
private:
	
public:
	list <Element>Elements;
	string sKey;
	int iCount;
	string sDescription;
	int iAmount;
	Element()
	{

	}
	Element(int count, string key, string description)
	{
	
		Element subItem;
		subItem.iAmount = count;
		subItem.sKey = key;
		iAmount = count;
		this->sKey = key;
		this->Elements.push_back(subItem);
		this->iCount = count;
		this->sDescription = description;
	}
	
};

 
class ElementList
 {
 
 public: 
	 map<string, string>elementlist;
	 ElementList() {}

	 class Helper
	 {
	 public:
		 
		 
			 static string& ltrim(string & s, const char* t = "\t\n")
			 {
				 s.erase(0, s.find_first_not_of(t));
				 return s;
			 }
			 static string& rtrim(string & s, const char* t = "\t\n")
			 {
				 s.erase(s.find_last_not_of(t));
				 return s;
			 }
			 static string& trim(string & s, const char* t = "\t\n")
			 {
				 return ltrim(rtrim(s, t), t);
			 }
		 
		 
	 };


	
	
	 list <string >ReadElementList(string pathIn)
	 {
		 //cout << "ReadElementList Source file date :" << endl;
		 list<string> textLines;
		 ifstream fileIn;
		 string str;
		 fileIn.open(pathIn);
		 if (fileIn.is_open())
		 {
			 while (getline(fileIn, str))
			 {
				 cout << "\t" << str << endl;
				 textLines.push_back(str);

				
			 }
			 cout << "\tFile opened successfullly " << endl;
		 }
		 else
			 cout << "\tFile not found " << endl;

		 fileIn.close();
		 cout << "ReadElementList End" << endl << endl;
		 return textLines;

	 }
	
	 //list<string>sortedLines;
	 list<string> SortElementList(list<string> textLines)
	 {
		 cout << "[SortElementList] Sort lines:" << endl;

		 list<string> sortedLines;
		 string str;
		 map<string, Element> mapElements = map<string, Element>();
		

		 for (string textLine : textLines)
		 {
			 {
				 string sKey;          // "VT7";
				 string amount;        // 1
				 string sDescription;  //"Транзистор MJD340";
				 int firstSpaceId = 0;
				
				 while (textLine[firstSpaceId] != ' ')
				 {
					 sKey += textLine[firstSpaceId++];
				 }

				 int lastSpaceId = textLine.length() - 1;
				 while (textLine[lastSpaceId] != ' ')
				 {
					 amount = textLine[lastSpaceId--] + amount;
				 }

				 for (int i = firstSpaceId; i < lastSpaceId; i++)
				 {
					 sDescription = sDescription + textLine[i];
				 }

				 sDescription =  Helper:: trim(sDescription);

				 int iAmount = atoi(amount.c_str());
				 if (mapElements.find(sDescription) != mapElements.end())
				 {
					 mapElements[sDescription].iCount += iAmount;

					 Element subElem;
					 subElem.iAmount = iAmount;
					 subElem.sKey = sKey;
					 mapElements[sDescription].Elements.push_back(subElem);

				 }
				 else
					 mapElements[sDescription] = Element(iAmount, sKey, sDescription);
			 }
		 }

		 for (auto element : mapElements)  //перебор и вывод всех элементов
		 {
			 if (element.second.iCount != 0)
			 {
				 bool isFirst = true;
				 string resultString = "\"" + element.first + "\"(" +
					 to_string(element.second.iCount) + ")\t";

				 cout << "\t\"" << element.first << "\"(" << element.second.iCount
					 << ")\t";

				 resultString += "\t[";
				 cout << "\t[";

				 for (Element subElement : element.second.Elements)
				 {
					 if (isFirst)
					 {
						 isFirst = false;
					 }
					 else
					 {
						 resultString += ",";
						 cout << ",";
					 }

					 resultString +=
						 subElement.sKey + "(" + to_string(subElement.iAmount) + ")";

					 cout << subElement.sKey << "(" << subElement.iAmount << ")";
				 }

				 cout << "]";
				 resultString += "]";
				 cout << endl;

				 sortedLines.push_back(resultString);
			 }
		 }

		 cout << "[SortElementList] End" << endl << endl;
		 return sortedLines;
	 }
	 

	 void SaveElementList(string pathOut, list<string> outLines)
	 {
		 cout << "[SaveElementList] Out path: " << pathOut << endl;

		 ofstream fileOut;
		 fileOut.open(pathOut, ofstream::app);
		 if (!fileOut.is_open())
		 {
			 cout << "\tFile open error" << endl;
		 }
		 else
		 {
			 fileOut << "\nВыходные данные " << endl;
			 for (string outLine : outLines) fileOut << outLine << endl;
			 cout << "\tFile saved successfully" << endl;
		 }
		 fileOut.close();

		 cout << "[SaveElementList] End" << endl << endl;
	 }

	 
 };
 
int main()
{

	setlocale(LC_ALL, "rus");

	ElementList lst;

	list<string> textLines = lst.ReadElementList("C:\\Users\\Дмитрий\\Desktop\\OOP_Dip\\input data.txt");
	list<string> sortedLines = lst.SortElementList(textLines);
	lst.SaveElementList("C:\\Users\\Дмитрий\\Desktop\\OOP_Dip\\output data.txt", sortedLines);
	return 0;
}
