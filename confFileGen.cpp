#include <stdio.h>

/**
 * An example for Builder pattern usage.
 * Builder pattern can be used for auto-generation of configuration files
 * which are composed of different parts, the order is important etc.
 * The main idea is to seperate logic and data from each other.
 */

class ConfBuilder
{
    public:
    ConfBuilder(){};
    virtual ~ConfBuilder(){};

    virtual void AddVersionAndInclusion() = 0;
    virtual void AddSource() = 0;
    virtual void AddDest() = 0;
};

class DummyNetworkProtocolConfBuilder : public ConfBuilder
{
    public:
    DummyNetworkProtocolConfBuilder(){};
    ~DummyNetworkProtocolConfBuilder(){};

    void AddVersionAndInclusion()
    {
        printf("\n@version: 1.0");
        printf("\n@include \"dummy.conf\"\n");        
    }

    void AddSource()
    {
        printf("\nsource {");
        printf("\n};\n");
    }

    void AddDest()
    {
        printf("\ndestination {");
        printf("\n};\n");
    }
};

class DummyNetworkProtocolConfGenerator
{
    
    ConfBuilder* _confBuilder;

    public:
    DummyNetworkProtocolConfGenerator(ConfBuilder* builder) : _confBuilder(builder){};

    void createDNPConf()
    {
        _confBuilder->AddVersionAndInclusion();
        _confBuilder->AddSource();
        _confBuilder->AddDest();        
    }

};

int main()
{

    DummyNetworkProtocolConfGenerator generator(new DummyNetworkProtocolConfBuilder());
    generator.createDNPConf();

    return 0;
}