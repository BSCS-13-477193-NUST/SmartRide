#include "Structures/DynamicRidePricing.h"

DynamicRidePricing::DynamicRidePricing() {
    priceTree = std::make_unique<AVLTree>();
}

DynamicRidePricing::~DynamicRidePricing() {}

double DynamicRidePricing::calculateBasePrice(double distance) const {
    return 50 + 80 * distance;
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