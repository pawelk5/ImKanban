#include <gtest/gtest.h>
#include <string>
#include "ContainerBase.hpp"

struct MockElement {
    std::string name;
};

struct MockData {
    std::string name;
};

class TestContainer : public ContainerBase<MockElement, MockData> {
public:
    TestContainer(const MockData& data) : ContainerBase<MockElement, MockData>(data) {}
};

class ContainerBaseTest : public testing::Test {
protected:
    TestContainer t_container;
    MockData t_data;
    ContainerBaseTest() 
        : t_container(t_data) { ; }
    
    void SetUp() override {
        t_data.name = "test";
        t_container = TestContainer(t_data);
    }

public:
    void AddElements(int count) {
        for (int i = 0; i < count; i++)
            t_container.AddElement(MockElement{"test" + std::to_string(i)});
    }
};

TEST_F(ContainerBaseTest, BaseConstructor)
{
    {
        MockData data {"test2"};
        TestContainer container(data);
        const auto &elements = container.GetElementArray();
        const auto &dataRef = container.GetDataRef();
        EXPECT_EQ(dataRef.name, "test2");
        EXPECT_EQ(elements.size(), 0);
    }
}

TEST_F(ContainerBaseTest, GetData)
{
    {
        auto data = t_container.GetData();
        EXPECT_EQ(data.name, "test");
        EXPECT_EQ(t_container.GetDataRef().name, "test");
    }
}

TEST_F(ContainerBaseTest, AddElement)
{
    {
        t_container.AddElement(MockElement({ "testElement1" }));
        EXPECT_EQ(t_container.GetElementArray().size(), 1);

        t_container.AddElement(std::make_shared<MockElement>(MockElement{ "testElement2" }));
        EXPECT_EQ(t_container.GetElementArray().size(), 2);

        EXPECT_EQ(t_container.At(0)->name, "testElement1");
        EXPECT_EQ(t_container.At(1)->name, "testElement2");
    }
}

TEST_F(ContainerBaseTest, At)
{
    {
        this->AddElements(3);

        EXPECT_NO_THROW(t_container.At(0));
        EXPECT_NO_THROW(t_container.At(1));
        EXPECT_NO_THROW(t_container.At(1));

        EXPECT_NO_THROW(t_container.At(t_container.GetElementArray().begin() ));
        EXPECT_NO_THROW(t_container.At(t_container.GetElementArray().begin() + 1));
        EXPECT_NO_THROW(t_container.At(t_container.GetElementArray().end() - 1));
    }
}

TEST_F(ContainerBaseTest, AtErrors)
{
    {
        MockData data {"test2"};
        TestContainer t_container2(data);

        EXPECT_THROW(t_container.At(-1), std::out_of_range);
        EXPECT_THROW(t_container.At(t_container.GetElementArray().size()), std::out_of_range);

        EXPECT_THROW(t_container.At(t_container.GetElementArray().begin() - 1), std::out_of_range);
        EXPECT_THROW(t_container.At(t_container.GetElementArray().end()), std::out_of_range);

        EXPECT_THROW(t_container.At(t_container2.GetElementArray().begin() - 1), std::out_of_range);
        EXPECT_THROW(t_container.At(t_container2.GetElementArray().begin()), std::out_of_range);
        EXPECT_THROW(t_container.At(t_container2.GetElementArray().begin() + 1), std::out_of_range);
        EXPECT_THROW(t_container.At(t_container2.GetElementArray().end()), std::out_of_range);
    }
}

TEST_F(ContainerBaseTest, InsertElement)
{
    {
        // Insert at index = size()
        t_container.InsertElement(std::make_shared<MockElement>(MockElement{"testElement"}), 0);
        EXPECT_EQ(t_container.GetElementArray().size(), 1);

        t_container.InsertElement(std::make_shared<MockElement>(MockElement{"testElement2"}), 0);
        EXPECT_EQ(t_container.GetElementArray().size(), 2);

        t_container.InsertElement(std::make_shared<MockElement>(MockElement{"testElement3"}), 1);
        EXPECT_EQ(t_container.GetElementArray().size(), 3);

        // Index out of range (-1), element expected to be added at the end
        t_container.InsertElement(std::make_shared<MockElement>(MockElement{"testElement4"}), -1);
        EXPECT_EQ(t_container.GetElementArray().size(), 4);

        // Index in the middle
        t_container.InsertElement(std::make_shared<MockElement>(MockElement{"testElement5"}), 2);
        EXPECT_EQ(t_container.GetElementArray().size(), 5);
    }
}


TEST_F(ContainerBaseTest, RemoveElement)
{
    {
        t_container.AddElement(MockElement({ "testElement" }));

        t_container.RemoveElement(t_container.GetElementArray().begin());
        EXPECT_EQ(t_container.GetElementArray().size(), 0);
    }

    {
        t_container.AddElement(MockElement({ "testElement" }));

        t_container.RemoveElement(0);
        EXPECT_EQ(t_container.GetElementArray().size(), 0);
    }
}

TEST_F(ContainerBaseTest, RemoveElementErrorsIndex)
{
    {
        this->AddElements(3);
        EXPECT_THROW(t_container.RemoveElement(-1), std::out_of_range);
        EXPECT_THROW(t_container.RemoveElement(t_container.GetElementArray().size()), std::out_of_range);
        t_container.RemoveElement(0);
        t_container.RemoveElement(0);
        t_container.RemoveElement(0);
        EXPECT_THROW(t_container.RemoveElement(0), std::out_of_range);
    }
}

TEST_F(ContainerBaseTest, RemoveElementErrorsIterator)
{
    {
        this->AddElements(3);
        MockData data {"test2"};
        TestContainer t_container2(data);

        EXPECT_THROW(t_container.RemoveElement(t_container2.GetElementArray().begin() - 1), std::out_of_range);
        EXPECT_THROW(t_container.RemoveElement(t_container2.GetElementArray().end()), std::out_of_range);
        t_container.RemoveElement(t_container.GetElementArray().begin());
        t_container.RemoveElement(t_container.GetElementArray().begin());
        t_container.RemoveElement(t_container.GetElementArray().begin());
        EXPECT_THROW(t_container.RemoveElement(t_container.GetElementArray().begin()), std::out_of_range);
    }
}

TEST_F(ContainerBaseTest, Update)
{
    {
        auto data = t_container.GetData();

        data.name = "changed";

        EXPECT_EQ(t_container.GetDataRef().name, "test");
        t_container.Update(data);
        EXPECT_EQ(t_container.GetDataRef().name, "changed");
    }
}