#include <iostream>
// #include <optional>

struct node {
   struct node* subTreeLeft{nullptr};
   int nodeValue{NULL};
   struct node* subTreeRight{nullptr};
};

// Inserts a given value in the binary tree
void insertValue(int value, struct node* treeRoot);
// Searches the tree for a given value
void searchTree(int value, struct node* root);
// Removes a given value from the binary tree
void removeValue(int value, struct node*& rootMain);

struct node* treeRoot{new struct node};

int main() {

   insertValue(80, treeRoot);
   insertValue(60, treeRoot);
   insertValue(15, treeRoot);
   insertValue(5, treeRoot);
   insertValue(75, treeRoot);
   insertValue(79, treeRoot);
   insertValue(73, treeRoot);
   insertValue(74, treeRoot);
   insertValue(22, treeRoot);
   insertValue(51, treeRoot);
   insertValue(40, treeRoot);
   insertValue(50, treeRoot);
   insertValue(58, treeRoot);

   searchTree(80, treeRoot);
   searchTree(60, treeRoot);
   searchTree(15, treeRoot);
   searchTree(5, treeRoot);
   searchTree(75, treeRoot);
   searchTree(79, treeRoot);
   searchTree(73, treeRoot);
   searchTree(74, treeRoot);
   searchTree(22, treeRoot);
   searchTree(51, treeRoot);
   searchTree(40, treeRoot);
   searchTree(50, treeRoot);
   searchTree(58, treeRoot);

   removeValue(15, treeRoot);
   removeValue(60, treeRoot);

   std::cout << "\nTree Post Removal\n" << std::endl;

   searchTree(80, treeRoot);
   searchTree(60, treeRoot);
   searchTree(15, treeRoot);
   searchTree(5, treeRoot);
   searchTree(75, treeRoot);
   searchTree(79, treeRoot);
   searchTree(73, treeRoot);
   searchTree(74, treeRoot);
   searchTree(22, treeRoot);
   searchTree(51, treeRoot);
   searchTree(40, treeRoot);
   searchTree(50, treeRoot);
   searchTree(58, treeRoot);

   // removeValue(8, treeRoot);

   // std::cout << "\nPost removal Tree" << std::endl;
   return 0;
}

void insertValue(int value, struct node* root) {
   if (root->nodeValue == NULL) {
      root->nodeValue = value;

   } else {
      while (true) {  // Iterates until it finds a valid spot to insert the
                      // value
         if (root->nodeValue > value) {
            if (root->subTreeLeft != nullptr) {
               root = root->subTreeLeft;

            } else {
               root->subTreeLeft = new struct node;
               root = root->subTreeLeft;
               root->nodeValue = value;
               break;
            }
         } else if (root->nodeValue <= value) {
            if (root->subTreeRight != nullptr) {
               root = root->subTreeRight;

            } else {
               root->subTreeRight = new struct node;
               root = root->subTreeRight;
               root->nodeValue = value;
               break;
            }
         }
      }
   }
}

void removeValue(int value, struct node*& rootMain) {
   struct node* previousNode{nullptr};
   struct node* root{
       rootMain};  // This is weird, but it helps later with removals

   while ((root->nodeValue != value)) {  // Seaches Value to Remove
      previousNode = root;

      if (root->nodeValue > value) {
         root = root->subTreeLeft;

      } else if (root->nodeValue <= value) {
         root = root->subTreeRight;
      }

      if (root == nullptr) {
         break;
      }
   }

   if (root != nullptr) {

      if ((root->subTreeLeft == nullptr) &&
          (root->subTreeRight == nullptr)) {  // Removing a Leaf Node
         delete root;

         if (previousNode->nodeValue > value) {
            previousNode->subTreeLeft = nullptr;

         } else if (previousNode->nodeValue <= value) {
            previousNode->subTreeRight = nullptr;
         }

      } else if ((root->subTreeLeft != nullptr) &&
                 (root->subTreeRight !=
                  nullptr)) {  // Removing node with two children
         struct node* lowestValue{root->subTreeRight};
         struct node* previousLowest{nullptr};

         while (lowestValue->subTreeLeft !=
                nullptr) {  // Search for replacement node
            previousLowest = lowestValue;
            lowestValue = lowestValue->subTreeLeft;
         }

         if (lowestValue->subTreeRight ==
             nullptr) {  // If the replacement does not have a child

            if (previousNode !=
                nullptr) {  // If target node is not the main tree root

               if (previousNode->nodeValue >
                   root->nodeValue) {  // Node to remove is on the left side of
                                       // the tree
                  previousNode->subTreeLeft = lowestValue;
                  lowestValue->subTreeLeft = root->subTreeLeft;

                  // Doing this ensures that, if the replacement node is right
                  // next To the target node, it won't end up point to itself
                  if (previousLowest != nullptr) {
                     lowestValue->subTreeRight = root->subTreeRight;
                  } else {
                     lowestValue->subTreeRight = nullptr;
                  }

               } else {  // Node to remove is on the right side of the tree
                  previousNode->subTreeRight = lowestValue;
                  lowestValue->subTreeLeft = root->subTreeLeft;

                  if (previousLowest != nullptr) {
                     lowestValue->subTreeRight = root->subTreeRight;
                  } else {
                     lowestValue->subTreeRight = nullptr;
                  }
               }

            } else {  // Target node is the main tree root

               lowestValue->subTreeLeft = root->subTreeLeft;

               if (previousLowest != nullptr) {
                  lowestValue->subTreeRight = root->subTreeRight;
               } else {
                  lowestValue->subTreeRight = nullptr;
               }

               rootMain = lowestValue;
            }

            delete root;

         } else {  // Replacement node has a child

            if (previousNode != nullptr) {

               if (previousNode->nodeValue >
                   root->nodeValue) {  // Target node is on the left side of the
                                       // tree
                  previousNode->subTreeLeft = lowestValue;

               } else {  // Target node is on the right side of the tree
                  previousNode->subTreeRight = lowestValue;
               }
               lowestValue->subTreeLeft = root->subTreeLeft;

               if (previousLowest != nullptr) {  // Replacement node is not
                                                 // right next to removal target
                  previousLowest->subTreeLeft = lowestValue->subTreeRight;
                  lowestValue->subTreeRight = root->subTreeRight;
               }

               delete root;

            } else {

               if (previousLowest != nullptr) {
                  previousLowest->subTreeLeft = lowestValue->subTreeRight;
                  lowestValue->subTreeRight = root->subTreeRight;
               }
               lowestValue->subTreeLeft = root->subTreeLeft;
               rootMain = lowestValue;

               delete root;
            }
         }

      } else {  // Removing node with a single child
         if (root->subTreeRight == nullptr) {  // Has child on left
            if (previousNode->nodeValue > root->nodeValue) {
               previousNode->subTreeLeft = root->subTreeLeft;
            } else {
               previousNode->subTreeRight = root->subTreeLeft;
            }
         } else if (root->subTreeLeft == nullptr) {  // Has child on right
            if (previousNode->nodeValue > root->nodeValue) {
               previousNode->subTreeLeft = root->subTreeRight;
            } else {
               previousNode->subTreeRight = root->subTreeRight;
            }
         }
         delete root;
      }
   } else {
      std::cout << "Value not found!" << std::endl;
   }
}

void searchTree(int valueSearched, struct node* root) {

   int depth{0};

   while (root != nullptr &&
          root->nodeValue != valueSearched) {  // Searches Value on the tree

      if (root->nodeValue > valueSearched) {
         root = root->subTreeLeft;

      } else if (root->nodeValue <= valueSearched) {
         root = root->subTreeRight;
      }

      depth++;
   }

   if (root == nullptr) {
      std::cout << "Value not found" << std::endl;

   } else {
      std::cout << "Value " << root->nodeValue << " found at depth " << depth
                << std::endl;
   }
}