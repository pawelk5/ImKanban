#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "ContainerBase.hpp"

/// Mock element storing only name
struct MockElement {
    std::string name;
};

/// Mock data of a container, storing only name
struct MockData {
    std::string name;
};

/// Mock class derived from ContainerBase class
class TestContainer : public ContainerBase<MockElement, MockData> {
public:
    /// Constructs a test container
    /// \param data data to be stored in the test container
    TestContainer(const MockData& data) : ContainerBase<MockElement, MockData>(data) {}
};

class ContainerBaseTest : public testing::Test {
protected:
    TestContainer t_container;
    MockData t_data;

    /// Constructor that initializes the container with empty data
    ContainerBaseTest() 
        : t_container(t_data) { ; }
    
    /// Setup function to initialize data before every test
    void SetUp() override {
        t_data.name = "test";
        t_container = TestContainer(t_data);
    }

public:
    /// Utility for adding elements to the container
    /// \param count number of added elements
    void AddElements(int count) {
        for (int i = 0; i < count; i++)
            t_container.AddElement(MockElement{"test" + std::to_string(i)});
    }
};

/// Test for Container constructor
/// Verifies if constructor stores data properly and stored array is empty
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

/// Test for GetData function
/// Verifies that GetData returns a copy of stored data
TEST_F(ContainerBaseTest, GetData)
{
    {
        auto data = t_container.GetData();
        EXPECT_EQ(data.name, "test");

        data.name = "changed";
        EXPECT_EQ(t_container.GetDataRef().name, "test");
    }
}


/// Test for adding elements to a container
TEST_F(ContainerBaseTest, AddElement)
{
    {
        t_container.AddElement(MockElement({ "testElement1" }));
        EXPECT_EQ(t_container.GetElementArray().size(), 1);

        t_container.AddElement(std::make_shared<MockElement>(MockElement{ "testElement2" }));
        EXPECT_EQ(t_container.GetElementArray().size(), 2);

        // Test if order wasn't changed
        EXPECT_EQ(t_container.At(0)->name, "testElement1");
        EXPECT_EQ(t_container.At(1)->name, "testElement2");
    }
}

/// Test for accessing elements using both indexes and iterators
TEST_F(ContainerBaseTest, At)
{
    {
        this->AddElements(3);

        /// Test using indexes
        EXPECT_NO_THROW(t_container.At(0));
        EXPECT_NO_THROW(t_container.At(1));
        EXPECT_NO_THROW(t_container.At(1));

        // Test using iterators
        EXPECT_NO_THROW(t_container.At(t_container.GetElementArray().begin() ));
        EXPECT_NO_THROW(t_container.At(t_container.GetElementArray().begin() + 1));
        EXPECT_NO_THROW(t_container.At(t_container.GetElementArray().end() - 1));
    }
}

/// Test for errors accessing elements using invalid indexes or iterators
TEST_F(ContainerBaseTest, AtErrors)
{
    {
        MockData data {"test2"};
        TestContainer t_container2(data);

        /// Test using invalid index
        EXPECT_THROW(t_container.At(-1), std::out_of_range);
        EXPECT_THROW(t_container.At(t_container.GetElementArray().size()), std::out_of_range);

        // Test using end iterator
        EXPECT_THROW(t_container.At(t_container.GetElementArray().end()), std::out_of_range);

        // Test using iterators of another container
        EXPECT_THROW(t_container.At(t_container2.GetElementArray().begin()), std::out_of_range);
        EXPECT_THROW(t_container.At(t_container2.GetElementArray().begin() + 1), std::out_of_range);
        EXPECT_THROW(t_container.At(t_container2.GetElementArray().end()), std::out_of_range);
    }
}

/// Test for inserting elements into container
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

/// Test for inserting elements into container using invalid indexes
TEST_F(ContainerBaseTest, InsertElementErrors)
{
    {
        // Insert at index = -1
        EXPECT_THROW(
            t_container.InsertElement(std::make_shared<MockElement>(MockElement{"testElement"}), -2),
            std::out_of_range
        );
        EXPECT_EQ(t_container.GetElementArray().size(), 0);

        // Insert at index = 1 (> size)
        EXPECT_THROW(
            t_container.InsertElement(std::make_shared<MockElement>(MockElement{"testElement"}), 1),
            std::out_of_range
        );
        EXPECT_EQ(t_container.GetElementArray().size(), 0);
    }
}


/// Test for removing elements from container
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

/// Test for errors when trying to remove elements using invalid indexes
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

/// Test for errors when trying to remove elements using invalid iterators
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

/// Test for Update function
/// Verifies that Update changes stored data
TEST_F(ContainerBaseTest, Update)
{
    {
        auto data = t_container.GetData();
        data.name = "changed";
        t_container.Update(data);
        EXPECT_EQ(t_container.GetDataRef().name, "changed");
    }
}