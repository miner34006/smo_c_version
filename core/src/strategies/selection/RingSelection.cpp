//
// Created by Богдан Полянок on 23.09.2018.
//

#include "RingSelection.hpp"

RingSelection::RingSelection(const size_t &elementPointer):
    elementPointer_(0)
{}

application_ptr
RingSelection::removeApplication(application_vector &applications)
{
    application_ptr fromPointerToEnd = RingSelection::search(applications, elementPointer_, applications.size());
    if (fromPointerToEnd == nullptr) {
        return RingSelection::search(applications, 0, elementPointer_);
    } else {
        return fromPointerToEnd;
    }
}

void RingSelection::movePointer(const size_t &bufferSize, const size_t &pointerPosition)
{
    if (pointerPosition == bufferSize) {
        elementPointer_ = 0;
    } else {
        elementPointer_ = pointerPosition + 1;
    }
}

application_ptr RingSelection::search(application_vector &applications,
                                         const size_t &fromIndex, const size_t &toIndex) {
    for (size_t i = fromIndex; i < toIndex; i++) {
        if (applications[i] != nullptr) {
            const application_ptr applicationToRemove = applications[i];
            applications[i] = nullptr;
            movePointer(applications.size(), i);
            return applicationToRemove;
        }
    }
    return nullptr;
}
