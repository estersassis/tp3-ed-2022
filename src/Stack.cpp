class Item {
    public:
        int left = -1, right = -1;
};

class Stack {
    public:
        Item *stack;
        int size = 0;

        Stack(int k) {
            stack = new Item[k];
            size = 0;
        };

        void Empilha(Item item) {
            stack[size] = item;
            size++;
        }

        void Desempilha() {
            size--;
        }
        
        ~Stack() { delete stack; };
};
