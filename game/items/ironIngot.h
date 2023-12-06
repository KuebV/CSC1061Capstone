//
// Created by Rob on 12/5/2023.
//

#ifndef CSC1061CAPSTONE_IRONINGOT_H
#define CSC1061CAPSTONE_IRONINGOT_H

class ironIngot : public item{
public:
    itemType GetType() override { return _type; }
    std::string GetName() override { return _name;}
    int GetCount() override { return _count; }
    double GetDropMultiplier() override { return _dropMultiplier; }

    void AddItem() override { _count++; }
    void RemoveItem() override { _count--; }

    bool isCraftable() override { return true; }
    std::map<itemType, int> GetCraftingRecipe() override {
        return {
                { itemType::Iron, 1},
                { itemType::Coal, 3},
        };
    }


private:
    std::string _name = "Iron Ingot";
    int _count = 0;
    itemType _type = itemType::IronIngot;
    double _dropMultiplier = 1.0;
    int _dropCount = 1;
};

#endif //CSC1061CAPSTONE_IRONINGOT_H
