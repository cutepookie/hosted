
#include "MB_DescriptionCommonUnit.h"
#include <algorithm>
#include <string.h>
#include "Game.h"
void DescriptionCommonUnit::insertPair (std::string key ,std::string value)
{
    if(!contains(key))
    {
        //MB_LOG("DescriptionCommonUnit: %s  -----   %s",key.c_str(),value.c_str());
        m_KeyValueMap.insert(make_pair(key,value));
    }
}

bool DescriptionCommonUnit::contains (std::string key)
{
    std::map<std::string, std::string>::iterator finder;
    finder = m_KeyValueMap.find(key);
    return finder != m_KeyValueMap.end();
}

DescriptionCommonUnit& DescriptionCommonUnit::queryValue (std::string key)
{
    m_value = contains(key)?m_KeyValueMap[key]:"";
    return *this;
}

int DescriptionCommonUnit::toInt (void)
{
    return atoi(m_value.c_str());
}

std::string DescriptionCommonUnit::toString (void)
{
    return m_value;
}

bool DescriptionCommonUnit::toBoolean (void)
{
    std::transform(m_value.begin(),
                   m_value.end(),
                   m_value.begin(),
                   ::tolower);
    return m_value == "true";
}
