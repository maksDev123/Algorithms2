
void swap(int* a, int* b);
size_t partition(std::vector<int>& v, size_t start, size_t end, bool random);
void recure(std::vector<int>& v, size_t start, size_t end, int& a, int& b, bool& flag1, bool& flag2, bool random);
double medianDeterministicPivot(std::vector<int>& v);
double medianUniformRandomPivot(std::vector<int>& v);

int quickSelect(std::vector<int>& v, int k, Pivot_f pivotFunction);

size_t deterministicPivot(std::vector<int>& data, size_t n);
size_t uniformRandomPivot(std::vector<int>& data, size_t n);
