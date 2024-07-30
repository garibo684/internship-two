#include "person.h"

void Person::SetWeight(double weight)
{
    if( m_weight != weight ) {
        m_weight = weight;
        emit WeightChanged();
    }
}
