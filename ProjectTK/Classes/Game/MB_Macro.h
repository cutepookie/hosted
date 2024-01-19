
#ifndef ProjectMB_MB_Macro_h
#define ProjectMB_MB_Macro_h

#define DECLARED_CLASS_WITH_BASE1(T,base)       class T:public base \
                                                {public: \
                                                    T();\
                                                    virtual ~T();
#define DECLARED_CLASS_END                      };

#define METHOD1(rType,fucName,p1)               rType fucName(p1);
#define METHOD2(rType,fucName,p1,p2)            rType fucName(p1,p2);
#define METHOD3(rType,fucName,p1,p2,p3)         rType fucName(p1,p2,p3);

#define METHOD1_V(rType,fucName,p1)               virtual rType fucName(p1);
#define METHOD2_V(rType,fucName,p1,p2)            virtual rType fucName(p1,p2);
#define METHOD3_V(rType,fucName,p1,p2,p3)         virtual rType fucName(p1,p2,p3);

#endif
