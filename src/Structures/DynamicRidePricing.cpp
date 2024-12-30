#include "Structures/DynamicRidePricing.h"

#include <memory>

#include "Structures/AVLprices.h"
#define PER_DISTANCE 0.5

DynamicRidePricing::DynamicRidePricing() {
    this->priceTree = std::make_unique<AVLTree>();
}

DynamicRidePricing::~DynamicRidePricing() {}

double DynamicRidePricing::calculateBasePrice(double distance) const {
    return 50 + PER_DISTANCE * distance;
}

double DynamicRidePricing::adjustedPrice(double basePrice, int time, int traffic, int demand) {
    double price = basePrice;
    if (time >= 8 && time <= 10) {
        price *= 1.2;
    } else if (time >= 17 && time <= 19) {
        price *= 1.5;
    }
    if (traffic == 1) {
        price *= 1.2;
    } else if (traffic == 2) {
        price *= 1.5;
    }
    if (demand == 1) {
        price *= 1.2;
    } else if (demand == 2) {
        price *= 1.5;
    }
    return price;
}

double DynamicRidePricing::calculatePrice(int time, int traffic, int demand, double distance) {
    AVLNode* node = priceTree->search(time, traffic, demand);
    if (node) {
        return node->data.price;
    } else {
        double basePrice = calculateBasePrice(distance);
        RidePricingData newData(time, traffic, demand, basePrice);
        priceTree->insert(newData);
        return basePrice;
    }
}