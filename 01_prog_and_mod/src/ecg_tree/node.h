#include <vector>
#include <string>

class Node {
    private:
        std::string name;
        std::vector<Node*> children;
    public:
        int node_id;  // ANCHOR - Aufgabe 1.2.1

        Node(const std::string& name="");
        virtual ~Node();

        const std::string get_name() const;
        void set_name(const std::string& name);

        int get_nr_children() const;
        Node * get_child(int i) const;
        void add_child(Node* child);

        // ANCHOR - Aufgabe 1.2.3
        std::ostream& print(std::ostream& str, int offset=0);
};

Node * create_complete_tree(int nr_child_nodes, int tree_depth);  // ANCHOR - Aufgabe 1.2.2

extern std::ostream& operator<<(std::ostream& os, Node * n_ptr);  // ANCHOR - Aufgabe 1.2.3

std::ostream& traverse_without_cycles(std::ostream& os, Node * n_ptr, int offset);  // ANCHOR - Aufgabe Z1
