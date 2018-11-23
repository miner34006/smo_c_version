//
// Created by Богдан Полянок on 23.09.2018.
//

#ifndef SMO_RINGSELECTION_HPP
#define SMO_RINGSELECTION_HPP

#include "SelectionStrategy.hpp"

class RingSelection: public SelectionStrategy {
public:
    explicit RingSelection(const size_t &elementPointer);
    application_ptr removeApplication(application_vector &applications);

private:
    size_t elementPointer_;

    application_ptr search(application_vector &applications,
                            const size_t &fromIndex, const size_t &toIndex);

    void movePointer(const size_t &bufferSize, const size_t &pointerPosition);
};

#endif //SMO_RINGSELECTION_HPP
