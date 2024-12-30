#ifndef DYNAMIC_RIDE_PRICING_H
#define DYNAMIC_RIDE_PRICING_H

#include <iostream>
#include <memory>

#include "Structures/AVLprices.h"

class DynamicRidePricing {
   public:
    DynamicRidePricing();
    ~DynamicRidePricing();
    double calculatePrice(int time, int traffic, int demand, double distance);

   private:
    std::unique_ptr<AVLTree> priceTree;
    double calculateBasePrice(double distance) const;
    double adjustedPrice(double basePrice, int time, int traffic, int demand);
};

#endif  // DYNAMIC_RIDE_PRICING_H