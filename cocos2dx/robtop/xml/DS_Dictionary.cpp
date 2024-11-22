#include "DS_Dictionary.h"

// source: https://forum.cocosengine.org/t/c-c-plist-reader-parser/1256/4

using namespace std;
using namespace cocos2d;
using namespace pugi;

#include "DS_Dictionary_Extra.h"

#define DS_DEBUG_MODE 0

#define COMPAT_STR(str) (m_compatible ? str : (const char[2]){str[0], 0})
#define COMPAT_STR_SV(str) (m_compatible ? std::string_view(str, sizeof(str) - 1) : std::string_view((const char[2]){str[0], 0}, 1))

//Constructor
DS_Dictionary::DS_Dictionary()
{
    //Initializers
    dictTree.push_back(xml_node());

    //Create default format
    xml_node plistNode = doc.append_child("plist");
    plistNode.append_attribute("version") = "1.0";
    plistNode.append_child("dict");

    //Set root dictTree node
    dictTree.back() = doc.child("plist").child("dict");
}

DS_Dictionary::~DS_Dictionary() {}

//Private methods
string DS_Dictionary::cleanStringWhiteSpace(const string& _str)
{
    string cleanStr = _str;
    cleanStr.erase(remove_if(cleanStr.begin(), cleanStr.end(),  static_cast<int(*)(int)>( isspace )), cleanStr.end());
    return cleanStr;
}

void DS_Dictionary::split(const string& src, const char* token, vector<string>& vect)
{
    int nend=0;
    int nbegin=0;
    while(nend != -1)
    {
        nend = src.find(token, nbegin);
        if(nend == -1)
            vect.push_back(src.substr(nbegin, src.length()-nbegin));
        else
            vect.push_back(src.substr(nbegin, nend-nbegin));
        nbegin = nend + strlen(token);
    }
}

bool DS_Dictionary::splitWithForm(const string& content, vector<string>& strs)
{
    // string is empty
    if(content.length() == 0){ return false; }

    int nPosLeft  = content.find('{');
    int nPosRight = content.find('}');

    // don't have '{' and '}'
    if(nPosLeft == (int)string::npos || nPosRight == (int)string::npos){ return false; }

    // '}' is before '{'
    if(nPosLeft > nPosRight){ return false; }

    string pointStr = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);

    // nothing between '{' and '}'
    if(pointStr.length() == 0){ return false; }

    int nPos1 = pointStr.find('{');
    int nPos2 = pointStr.find('}');

    // contain '{' or '}' 
    if(nPos1 != (int)string::npos || nPos2 != (int)string::npos){ return false; }

    split(pointStr, ",", strs);
    if (strs.size() != 2 || strs[0].length() == 0 || strs[1].length() == 0)
    {
        return false;
    }

    return true;
}

bool DS_Dictionary::rectFromString(const string& pszContent, CCRect& rect)
{
    //Clean white spaces
    string content = cleanStringWhiteSpace(pszContent);

    // find the first '{' and the third '}'
    int nPosLeft  = content.find('{');
    int nPosRight = content.find('}');
    for (int i = 1; i < 3; ++i)
    {
        if (nPosRight == (int)string::npos)
        {
            break;
        }
        nPosRight = content.find('}', nPosRight + 1);
    }
    if(nPosLeft == (int)string::npos || nPosRight == (int)string::npos){ return false; }

    content = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
    int nPointEnd = content.find('}');
    if(nPointEnd == (int)string::npos){ return false; }
    nPointEnd = content.find(',', nPointEnd);
    if(nPointEnd == (int)string::npos){ return false; }

    // get the point string and size string
    string pointStr = content.substr(0, nPointEnd);
    string sizeStr  = content.substr(nPointEnd + 1, content.length() - nPointEnd);

    // split the string with ','
    vector<string> pointInfo;
    if(!splitWithForm(pointStr, pointInfo)){ return false; }
    vector<string> sizeInfo;
    if(!splitWithForm(sizeStr, sizeInfo)){ return false; }

    float x = (float) atof(pointInfo[0].c_str());
    float y = (float) atof(pointInfo[1].c_str());
    float width  = (float) atof(sizeInfo[0].c_str());
    float height = (float) atof(sizeInfo[1].c_str());

    rect = CCRect(CCPoint(x, y), CCPoint(width, height));
    return true;
}

bool DS_Dictionary::vec2FromString(const string& pszContent, CCPoint& vec2)
{
    vector<string> strs;
    if(!splitWithForm(cleanStringWhiteSpace(pszContent), strs))
    {
        return false;
    }

    float x = (float) atof(strs[0].c_str());
    float y = (float) atof(strs[1].c_str());

    vec2 = CCPoint(x, y);
    return true;
}

//Methods
bool DS_Dictionary::loadRootSubDictFromFile(const char* fileName)
{
    //Clear existing
    dictTree.clear();
    dictTree.push_back(xml_node());

    auto* fileUtils = CCFileUtils::sharedFileUtils();
    auto fullPath = fileUtils->fullPathForFilename(fileName);

    //Open file
    xml_parse_result result = doc.load_file(fullPath.c_str());

    if (!result) {
        auto writablePath = fileUtils->getWritablePath();
        result = doc.load_file((writablePath + fileName).c_str());
    }

    if (!result) {
        if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: FAILED TO PARSE XML FILE: ").append(fileName).append(": WITH ERROR: ").append(result.description()).c_str()); }
        return false;
    }

    m_compatible = doc.child("plist").attribute("gjver").as_int() < 2;

    //Set root dictTree node
    dictTree.back() = doc.child("plist").child("dict");
    return true;
}

bool DS_Dictionary::saveRootSubDictToFile(const char* fileName)
{
    //Attempt to save file
    bool result = doc.save_file(fileName);

    if(!result)
    {
        if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: FAILED TO SAVE XML FILE: ").append(fileName).c_str()); }
    }

    return result;
}

bool DS_Dictionary::stepIntoSubDictWithKey(const char* key)
{
    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
    {
        if(node.child_value() == string(key) && node.next_sibling() == node.next_sibling(COMPAT_STR("dict")))
        {
            dictTree.push_back(node.next_sibling());
            return true;
        }
    }

    if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: FAILED TO STEP INTO XML DICTIONARY WITH KEY: ").append(key).c_str()); }
    return false;
}

void DS_Dictionary::stepOutOfSubDict()
{
    if(dictTree.size() > 1)
    {
        dictTree.pop_back();
    }
}

void DS_Dictionary::stepBackToRootSubDict()
{
    if(dictTree.size() > 1)
    {
        dictTree.clear();
        dictTree.push_back(xml_node());
        dictTree.back() = doc.child("plist").child("dict");
    }
}

unsigned int DS_Dictionary::getNumKeys()
{
    unsigned int numKeys = 0;

    for(xml_node node = dictTree.back().first_child(); node; node = node.next_sibling().next_sibling())
    {
        numKeys++;
    }

    return numKeys;
}

string DS_Dictionary::getKey(unsigned int index)
{
    unsigned int count = 0;

    for(xml_node node = dictTree.back().first_child(); node; node = node.next_sibling().next_sibling())
    {
        if(count == index){ return node.child_value(); }
        count++;
    }

    return string();
}

vector<string> DS_Dictionary::getAllKeys()
{
    vector<string> strings;

    for(xml_node node = dictTree.back().first_child(); node; node = node.next_sibling().next_sibling())
    {
        strings.push_back(node.child_value());
    }

    return strings;
}

unsigned int DS_Dictionary::getIndexOfKey(const char* key)
{
    unsigned int count = 0;

    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
    {
        if(node.child_value() == string(key))
        {
            return count;
        }
        count++;
    }

    return 0;
}

unsigned int DS_Dictionary::getIndexOfKeyWithClosestAlphaNumericalMatch(const char* key)
{
    unsigned int count = 0;

    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
    {
        if(alphaNumericallyLessThan(key, node.child_value()))
        {
            return count;
        }
        count++;
    }

    return 0;
}

void DS_Dictionary::removeKey(unsigned int index)
{
    unsigned int count = 0;

    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
    {
        if(count == index)
        { 
            //Remove the node
            dictTree.back().remove_child(node.next_sibling());
            dictTree.back().remove_child(node);
            break;
        }
        count++;
    }
}

void DS_Dictionary::removeKey(const char* key)
{
    //Check to see if the value already exists withing the current sub dict
    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
    {
        if(node.child_value() == string(key))
        {
            //Already exists, remove the node
            dictTree.back().remove_child(node.next_sibling());
            dictTree.back().remove_child(node);
            break;
        }
    }
}

void DS_Dictionary::removeAllKeys()
{
    while(xml_node node = dictTree.back().child(COMPAT_STR("key")))
    {
        dictTree.back().remove_child(node.next_sibling());
        dictTree.back().remove_child(node);
    }
}

int DS_Dictionary::getIntegerForKey(const char* key)
{
    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key"))) {
        if (node.child_value() == std::string_view(key) && node.next_sibling().name() == COMPAT_STR_SV("integer")) {
            return strtol(node.next_sibling().child_value(), NULL, 10);
        }
    }

    if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: FAILED TO READ INTEGER VALUE FOR KEY: ").append(key).c_str()); }
    return 0;
}

bool DS_Dictionary::getBoolForKey(const char* key)
{
    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
    {
        if(node.child_value() == string(key) && (node.next_sibling() == node.next_sibling(COMPAT_STR("true")) || node.next_sibling() == node.next_sibling(COMPAT_STR("false"))))
        {
            if(node.next_sibling() == node.next_sibling(COMPAT_STR("true"))){ return true; }
            if(node.next_sibling() == node.next_sibling(COMPAT_STR("false"))){ return false; }
        }
    }

    if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: FAILED TO READ BOOL VALUE FOR KEY: ").append(key).c_str()); }
    return false;
}

float DS_Dictionary::getFloatForKey(const char* key)
{
    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
    {
        if(node.child_value() == string(key) && (node.next_sibling() == node.next_sibling(COMPAT_STR("integer")) || node.next_sibling() == node.next_sibling(COMPAT_STR("real"))))
        {
            return strtod(node.next_sibling().child_value(), NULL);
        }
    }

    if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: FAILED TO READ FLOAT VALUE FOR KEY: ").append(key).c_str()); }
    return 0;
}

string DS_Dictionary::getStringForKey(const char* key)
{
    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
    {
        if(node.child_value() == string(key) && node.next_sibling() == node.next_sibling(COMPAT_STR("string")))
        {
            return node.next_sibling().child_value();
        }
    }

    if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: FAILED TO READ STRING VALUE FOR KEY: ").append(key).c_str()); }
    return "";
}

CCPoint DS_Dictionary::getVec2ForKey(const char* key)
{
    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
    {
        if(node.child_value() == string(key) && node.next_sibling() == node.next_sibling(COMPAT_STR("string")))
        {
            CCPoint vec2;

            if(vec2FromString(node.next_sibling().child_value(), vec2))
            {
                return vec2;
            }

            else
            {
                if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: MALFORMED VEC2 VALUE FOR KEY: ").append(key).c_str()); }
                return CCPoint();
            }
        }
    }

    if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: FAILED TO READ VEC2 VALUE FOR KEY: ").append(key).c_str()); }
    return CCPoint();
}

CCRect DS_Dictionary::getRectForKey(const char* key)
{
    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
    {
        if(node.child_value() == string(key) && node.next_sibling() == node.next_sibling(COMPAT_STR("string")))
        {
            CCRect rect;

            if(rectFromString(node.next_sibling().child_value(), rect))
            {
                return rect;
            }

            else
            {
                if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: MALFORMED RECT VALUE FOR KEY: ").append(key).c_str()); }
                return CCRect();
            }
        }
    }

    if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: FAILED TO READ RECT VALUE FOR KEY: ").append(key).c_str()); }
    return CCRect();
}

vector<string> DS_Dictionary::getStringArrayForKey(const char* key)
{
    for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
    {
        if(node.child_value() == string(key) && node.next_sibling() == node.next_sibling(COMPAT_STR("array")))
        {
            vector<string> value;

            for(xml_node arrayNode = node.next_sibling().first_child(); arrayNode; arrayNode = arrayNode.next_sibling())
            {
                value.push_back(arrayNode.child_value());
            }

            return value;
        }
    }

    if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: FAILED TO READ STRING VALUE FOR ARRAY KEY: ").append(key).c_str()); }
    return vector<string>();
}

vector<CCPoint> DS_Dictionary::getVec2ArrayForKey(const char* key)
{
    vector<string> strings = getStringArrayForKey(key);
    vector<CCPoint> vectorVec2;

    for(int i=0; i<strings.size(); i++)
    {
        vectorVec2.push_back(CCPoint());
        if(!vec2FromString(strings[i], vectorVec2.back()))
        {
            if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: MALFORMED VEC2 VALUE FOR ARRAY KEY: ").append(key).c_str()); }
            vectorVec2.clear();
            break;
        }
    }

    return vectorVec2;
}

vector<CCRect> DS_Dictionary::getRectArrayForKey(const char* key)
{
    vector<string> strings = getStringArrayForKey(key);
    vector<CCRect> vectorRect;

    for(int i=0; i<strings.size(); i++)
    {
        vectorRect.push_back(CCRect());
        if(!rectFromString(strings[i], vectorRect.back()))
        {
            if(DS_DEBUG_MODE){ printf("%s \n",string("DS_ENGINE:> :ERROR: MALFORMED RECT VALUE FOR ARRAY KEY: ").append(key).c_str()); }
            vectorRect.clear();
            break;
        }
    }

    return vectorRect;
}

void DS_Dictionary::setSubDictForKey(const char* key){ setSubDictForKey(key, false); }
void DS_Dictionary::setSubDictForKey(const char* key, bool alphaNumericallySorted, bool unk)
{
    //Check to see if the sub dict already exists withing the current sub dict
    removeKey(key);

    //Create a key value pair as a child of the current sub dict
    xml_node keyNode;
    bool appendKey = true;
    if(alphaNumericallySorted)
    {
        for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
        {
            if(!alphaNumericallyLessThan(node.child_value(), key))
            {
                keyNode = dictTree.back().insert_child_before(COMPAT_STR("key"), node);
                appendKey = false;
                break;
            }
        }
    }

    if(appendKey){ keyNode = dictTree.back().append_child(COMPAT_STR("key")); }
    keyNode.append_child(node_pcdata).set_value(key);
    dictTree.back().insert_child_after(COMPAT_STR("dict"), keyNode);
}

void DS_Dictionary::setIntegerForKey(const char* key, int value){ setIntegerForKey(key, value, false); }
void DS_Dictionary::setIntegerForKey(const char* key, int value, bool alphaNumericallySorted)
{
    //Create a string from the input value
    stringstream stream;
    stream << value;

    //Check to see if the value already exists withing the current sub dict
    removeKey(key);

    //Create a key value pair as a child of the current sub dict
    xml_node keyNode;
    bool appendKey = true;
    if(alphaNumericallySorted)
    {
        for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
        {
            if(!alphaNumericallyLessThan(node.child_value(), key))
            {
                keyNode = dictTree.back().insert_child_before(COMPAT_STR("key"), node);
                appendKey = false;
                break;
            }
        }
    }

    if(appendKey){ keyNode = dictTree.back().append_child(COMPAT_STR("key")); }
    keyNode.append_child(node_pcdata).set_value(key);
    dictTree.back().insert_child_after(COMPAT_STR("integer"), keyNode).append_child(node_pcdata).set_value(stream.str().c_str());
}

void DS_Dictionary::setBoolForKey(const char* key, bool value){ setBoolForKey(key, value, false); }
void DS_Dictionary::setBoolForKey(const char* key, bool value, bool alphaNumericallySorted)
{
    //Check to see if the value already exists withing the current sub dict
    removeKey(key);

    //Create a key value pair as a child of the current sub dict
    xml_node keyNode;
    bool appendKey = true;
    if(alphaNumericallySorted)
    {
        for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
        {
            if(!alphaNumericallyLessThan(node.child_value(), key))
            {
                keyNode = dictTree.back().insert_child_before(COMPAT_STR("key"), node);
                appendKey = false;
                break;
            }
        }
    }

    if(appendKey){ keyNode = dictTree.back().append_child(COMPAT_STR("key")); }
    keyNode.append_child(node_pcdata).set_value(key);
    if(value){ dictTree.back().insert_child_after(COMPAT_STR("true"), keyNode); }
    else     { dictTree.back().insert_child_after(COMPAT_STR("false"), keyNode); }
}

void DS_Dictionary::setFloatForKey(const char* key, float value){ setFloatForKey(key, value, false); }
void DS_Dictionary::setFloatForKey(const char* key, float value, bool alphaNumericallySorted)
{
    //Create a string from the input value
    stringstream stream;
    stream << value;

    //Check to see if the value already exists withing the current sub dict
    removeKey(key);

    //Create a key value pair as a child of the current sub dict
    xml_node keyNode;
    bool appendKey = true;
    if(alphaNumericallySorted)
    {
        for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
        {
            if(!alphaNumericallyLessThan(node.child_value(), key))
            {
                keyNode = dictTree.back().insert_child_before(COMPAT_STR("key"), node);
                appendKey = false;
                break;
            }
        }
    }

    if(appendKey){ keyNode = dictTree.back().append_child(COMPAT_STR("key")); }
    keyNode.append_child(node_pcdata).set_value(key);
    dictTree.back().insert_child_after(COMPAT_STR("real"), keyNode).append_child(node_pcdata).set_value(stream.str().c_str());
}

void DS_Dictionary::setStringForKey(const char* key, const string& value){ setStringForKey(key, value, false); }
void DS_Dictionary::setStringForKey(const char* key, const string& value, bool alphaNumericallySorted)
{
    //Check to see if the value already exists withing the current sub dict
    removeKey(key);

    //Create a key value pair as a child of the current sub dict
    xml_node keyNode;
    bool appendKey = true;
    if(alphaNumericallySorted)
    {
        for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
        {
            if(!alphaNumericallyLessThan(node.child_value(), key))
            {
                keyNode = dictTree.back().insert_child_before(COMPAT_STR("key"), node);
                appendKey = false;
                break;
            }
        }
    }

    if(appendKey){ keyNode = dictTree.back().append_child(COMPAT_STR("key")); }
    keyNode.append_child(node_pcdata).set_value(key);
    dictTree.back().insert_child_after(COMPAT_STR("string"), keyNode).append_child(node_pcdata).set_value(value.c_str());
}

void DS_Dictionary::setVec2ForKey(const char* key, const CCPoint& value){ setVec2ForKey(key, value, false); }
void DS_Dictionary::setVec2ForKey(const char* key, const CCPoint& value, bool alphaNumericallySorted)
{
    //Create a string from the input value
    stringstream stream;
    stream << "{";
    stream << value.x;
    stream << ",";
    stream << value.y;
    stream << "}";

    //Check to see if the value already exists withing the current sub dict
    removeKey(key);

    //Create a key value pair as a child of the current sub dict
    xml_node keyNode;
    bool appendKey = true;
    if(alphaNumericallySorted)
    {
        for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
        {
            if(!alphaNumericallyLessThan(node.child_value(), key))
            {
                keyNode = dictTree.back().insert_child_before(COMPAT_STR("key"), node);
                appendKey = false;
                break;
            }
        }
    }

    if(appendKey){ keyNode = dictTree.back().append_child(COMPAT_STR("key")); }
    keyNode.append_child(node_pcdata).set_value(key);
    dictTree.back().insert_child_after(COMPAT_STR("string"), keyNode).append_child(node_pcdata).set_value(stream.str().c_str());
}

void DS_Dictionary::setRectForKey(const char* key, const CCRect& value){ setRectForKey(key, value, false); }
void DS_Dictionary::setRectForKey(const char* key, const CCRect& value, bool alphaNumericallySorted)
{
    //Create a string from the input value
    stringstream stream;
    stream << "{{";
    stream << value.origin.x;
    stream << ",";
    stream << value.origin.y;
    stream << "},{";
    stream << value.size.width;
    stream << ",";
    stream << value.size.height;
    stream << "}}";

    //Check to see if the value already exists withing the current sub dict
    removeKey(key);

    //Create a key value pair as a child of the current sub dict
    xml_node keyNode;
    bool appendKey = true;
    if(alphaNumericallySorted)
    {
        for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
        {
            if(!alphaNumericallyLessThan(node.child_value(), key))
            {
                keyNode = dictTree.back().insert_child_before(COMPAT_STR("key"), node);
                appendKey = false;
                break;
            }
        }
    }

    if(appendKey){ keyNode = dictTree.back().append_child(COMPAT_STR("key")); }
    keyNode.append_child(node_pcdata).set_value(key);
    dictTree.back().insert_child_after(COMPAT_STR("string"), keyNode).append_child(node_pcdata).set_value(stream.str().c_str());
}

void DS_Dictionary::setStringArrayForKey(const char* key, const vector<string>& value){ setStringArrayForKey(key, value, false); }
void DS_Dictionary::setStringArrayForKey(const char* key, const vector<string>& value, bool alphaNumericallySorted)
{
    //Check to see if the value already exists withing the current sub dict
    removeKey(key);

    //Create a key value pair as a child of the current sub dict
    xml_node keyNode;
    xml_node arrayNode;
    bool appendKey = true;
    if(alphaNumericallySorted)
    {
        for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
        {
            if(!alphaNumericallyLessThan(node.child_value(), key))
            {
                keyNode = dictTree.back().insert_child_before(COMPAT_STR("key"), node);
                appendKey = false;
                break;
            }
        }
    }

    if(appendKey){ keyNode = dictTree.back().append_child(COMPAT_STR("key")); }
    keyNode.append_child(node_pcdata).set_value(key);
    arrayNode = dictTree.back().insert_child_after(COMPAT_STR("array"), keyNode);

    //Fill the array
    for(int i=0; i<value.size(); i++)
    {
        arrayNode.append_child(COMPAT_STR("string")).append_child(node_pcdata).set_value(value[i].c_str());
    }
}

void DS_Dictionary::setVec2ArrayForKey(const char* key, const vector<CCPoint>& value){ setVec2ArrayForKey(key, value, false); }
void DS_Dictionary::setVec2ArrayForKey(const char* key, const vector<CCPoint>& value, bool alphaNumericallySorted)
{
    //Check to see if the value already exists withing the current sub dict
    removeKey(key);

    //Create a key value pair as a child of the current sub dict
    xml_node keyNode;
    xml_node arrayNode;
    bool appendKey = true;
    if(alphaNumericallySorted)
    {
        for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
        {
            if(!alphaNumericallyLessThan(node.child_value(), key))
            {
                keyNode = dictTree.back().insert_child_before(COMPAT_STR("key"), node);
                appendKey = false;
                break;
            }
        }
    }

    if(appendKey){ keyNode = dictTree.back().append_child(COMPAT_STR("key")); }
    keyNode.append_child(node_pcdata).set_value(key);
    arrayNode = dictTree.back().insert_child_after(COMPAT_STR("array"), keyNode);

    //Fill the array
    for(int i=0; i<value.size(); i++)
    {
        //Create a string from the input value
        stringstream stream;
        stream << "{";
        stream << value[i].x;
        stream << ",";
        stream << value[i].y;
        stream << "}";

        arrayNode.append_child(COMPAT_STR("string")).append_child(node_pcdata).set_value(stream.str().c_str());
    }
}

void DS_Dictionary::setRectArrayForKey(const char* key, const vector<CCRect>& value){ setRectArrayForKey(key, value, false); }
void DS_Dictionary::setRectArrayForKey(const char* key, const vector<CCRect>& value, bool alphaNumericallySorted)
{
    //Check to see if the value already exists withing the current sub dict
    removeKey(key);

    //Create a key value pair as a child of the current sub dict
    xml_node keyNode;
    xml_node arrayNode;
    bool appendKey = true;
    if(alphaNumericallySorted)
    {
        for(xml_node node = dictTree.back().child(COMPAT_STR("key")); node; node = node.next_sibling(COMPAT_STR("key")))
        {
            if(!alphaNumericallyLessThan(node.child_value(), key))
            {
                keyNode = dictTree.back().insert_child_before(COMPAT_STR("key"), node);
                appendKey = false;
                break;
            }
        }
    }

    if(appendKey){ keyNode = dictTree.back().append_child(COMPAT_STR("key")); }
    keyNode.append_child(node_pcdata).set_value(key);
    arrayNode = dictTree.back().insert_child_after(COMPAT_STR("array"), keyNode);

    //Fill the array
    for(int i=0; i<value.size(); i++)
    {
        //Create a string from the input value
        stringstream stream;
        stream << "{{";
        stream << value[i].origin.x;
        stream << ",";
        stream << value[i].origin.y;
        stream << "},{";
        stream << value[i].size.width;
        stream << ",";
        stream << value[i].size.height;
        stream << "}}";

        arrayNode.append_child(COMPAT_STR("string")).append_child(node_pcdata).set_value(stream.str().c_str());
    }
}

// robtop additions
void DS_Dictionary::addBoolValuesToMapForKey(std::map<std::string, bool>&, char const *, bool) {
    ROB_UNIMPLEMENTED();
}
void DS_Dictionary::addBoolValuesToMapForKeySpecial(std::map<std::string, bool>&, char const *, bool) {
    ROB_UNIMPLEMENTED();
}
void DS_Dictionary::copyFile(char const *, char const *) {
    ROB_UNIMPLEMENTED();
}

bool DS_Dictionary::loadRootSubDictFromCompressedFile(char const* path) {
    CCLOG("DS_Dictionary::loadRootSubDictFromCompressedFile: %s", path);
    std::string dir = CCFileUtils::sharedFileUtils()->getWritablePath();
    auto fullPath = dir + path;
    CCLOG("%s", fullPath.c_str());

    unsigned long size;
    auto* data = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "rb", &size);
    if (!data) return false;

    auto decoded = ZipUtils::decompressString2(data, true, size, 11);
    delete[] data;

    return loadRootSubDictFromString(decoded);
}

bool DS_Dictionary::loadRootSubDictFromString(std::string const& str) {
    if (str.empty()) return false;

    dictTree.clear();
    dictTree.push_back(xml_node());

    xml_parse_result result = doc.load(str.c_str());

    if (!result) {
        return false;
    }

    m_compatible = doc.child("plist").attribute("gjver").as_int() < 2;

    dictTree.back() = doc.child("plist").child("dict");
    return true;
}

bool DS_Dictionary::saveRootSubDictToCompressedFile(char const *) {
    ROB_UNIMPLEMENTED();
}
std::string DS_Dictionary::saveRootSubDictToString(void) {
    ROB_UNIMPLEMENTED();
}

void DS_Dictionary::setBoolMapForKey(char const *, std::map<std::string, bool>&) {
    ROB_UNIMPLEMENTED();
}
void DS_Dictionary::setArrayForKey(char const *, CCArray*) {
    ROB_UNIMPLEMENTED();
}
CCArray* DS_Dictionary::getArrayForKey(char const *, bool) {
    ROB_UNIMPLEMENTED();
}
CCDictionary* DS_Dictionary::getDictForKey(char const* key, bool unk) {
    if (key == nullptr || unk || this->stepIntoSubDictWithKey(key)) {
        auto* dict = CCDictionary::create();

        for (auto node = dictTree.back().first_child(); node; node = node.next_sibling().next_sibling()) {
            CCObject* object = nullptr;
            if (node.next_sibling().name() == COMPAT_STR_SV("dict")) {
                dictTree.push_back(node.next_sibling());
                bool isArr = this->getBoolForKey("_isArr");
                int cek = this->getIntegerForKey("kCEK");
                if (cek == 0) {
                    if (isArr) {
                        object = this->getArrayForKey(node.child_value(), true);
                    } else {
                        object = this->getDictForKey(node.child_value(), true);
                    }
                } else {
                    if (cek == -1) {
                        // ??
                        cek = this->getIntegerForKey("kCEK");
                    }
                    object = ObjectDecoder::sharedDecoder()->getDecodedObject(cek, this);
                    stepOutOfSubDict();
                }
            } else if (node.next_sibling().name() == COMPAT_STR_SV("true")) {
                object = CCString::create("1");
            } else {
                object = CCString::create(node.next_sibling().child_value());
            }

            if (object != nullptr) {
                dict->setObject(object, node.child_value());
            }
        }

        if (key != nullptr) {
            this->stepOutOfSubDict();
        }
        return dict;
    } else {
        // im not sure this is what rob is actually doing
        return CCDictionary::create();
    }
}
void DS_Dictionary::setDictForKey(char const *, CCDictionary*) {
    ROB_UNIMPLEMENTED();
}