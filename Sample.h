//
// Created by ASUS on 27/12/2020.
//

#ifndef CPP20_SAMPLE_H
#define CPP20_SAMPLE_H

struct java_lang_String {};


struct com_company_Sample
{
    java_lang_String* sampleStringField;
};

com_company_Sample* com_company_Sample$$init()
{
    com_company_Sample* newInstance = (com_company_Sample*)malloc(sizeof(com_company_Sample));



    return newInstance;
}

java_lang_String com_company_Sample$$getSampleStringField(com_company_Sample* _this)
{
    return _this->sampleStringField;
}

#endif //CPP20_SAMPLE_H
