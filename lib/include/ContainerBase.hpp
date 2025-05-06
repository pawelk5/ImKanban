#pragma once
#include "api.h"
#include <stdexcept>
#include <vector>
#include <memory>

template <typename Element, typename ContainerData>
class EXPORT_API ContainerBase {
public:
    using ElementPointer = std::shared_ptr<Element>;
    using ElementArray = std::vector<ElementPointer>;
    using ElementArrayIterator = ElementArray::const_iterator;

protected:
    ContainerBase(const ContainerData &data) {
        Update(data);
    }

public:
    ElementPointer& At(ElementArrayIterator iter) {
        return At(AsIndex(iter));
    }

    ElementPointer& At(int index) {
        if (!IsValid(index))
            throw std::out_of_range(invalidIndex);

        return m_array.at((uint32_t)index);
    }

    const ElementArray &GetElementArray() const {
        return m_array;
    }

    ContainerData GetData() const {
        return m_data;
    }

    const ContainerData& GetDataRef() const {
        return m_data;
    }

    void Update(const ContainerData &data) {
        m_data = data;
    }

    void AddElement(const Element &element) {
        AddElement(std::make_shared<Element>(element));
    }

    void AddElement(const ElementPointer &element) {
        m_array.push_back(element);
    }

    void RemoveElement(ElementArrayIterator it) {
        if (!IsValid(it))
            throw std::out_of_range(invalidIterator);
        m_array.erase(it);
    }

    void RemoveElement(int index) {
        if (!IsValid(index))
            throw std::out_of_range(invalidIndex);
        RemoveElement(m_array.begin() + index);
    }

    void InsertElement(const ElementPointer &card, int index) {
        if (index == -1)
            m_array.push_back(card);
        else if (IsValid(index) || index == m_array.size()) {
            auto it = m_array.begin() + index;
            m_array.insert(it, card);
        }
        else
            throw std::out_of_range(invalidIndex);
    }

    int AsIndex(ElementArrayIterator iter) {
        if (!IsValid(iter))
            throw std::out_of_range(invalidIterator);
        return std::distance((ElementArrayIterator)m_array.begin(), iter);
    }

    ElementArrayIterator AsIterator(int index) {
        if (!IsValid(index))
            throw std::out_of_range(invalidIndex);
        return m_array.begin() + index;
    }

protected:
    ElementArray m_array;
    ContainerData m_data;
   
protected:
    bool IsValid(int index) {
        return index >= 0 && index < m_array.size();
    }

    bool IsValid(ElementArrayIterator iter) {
        return iter >= m_array.begin() && iter < m_array.end();
    }

    const char* invalidIterator = "Invalid iterator!";
    const char* invalidIndex = "Invalid index!";
};