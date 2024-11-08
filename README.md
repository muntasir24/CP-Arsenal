## 1. Matrix Neighbor Validation using `dx` and `dy` Arrays

Given a matrix of size `n x m`, for any cell `(x, y)`, we want to find its valid neighboring cells.



```cpp
vector<pair<int, int>> getValidNeighbors(int n, int m, int x, int y) {
    // Define the direction arrays
    int dx[] = {0, -1, 1, 0};  // Right, Up, Down, Left
    int dy[] = {1, 0, 0, -1};  // Right, Up, Down, Left
    vector<pair<int, int>> validNeighbors;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];  
        int ny = y + dy[i]; 

        if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
            validNeighbors.push_back({nx, ny});  
        }
    }

    return validNeighbors;
}
```
```cpp
int main() {
    int n = 3, m = 3;   // Matrix size
    int x = 2, y = 0;   // Position to check neighbors

    vector<pair<int, int>> validNeighbors = getValidNeighbors(n, m, x, y);

    // Output valid neighbors
    cout << "Valid neighbors:" << endl;
    for (auto neighbor : validNeighbors) {
        cout << "(" << neighbor.first << ", " << neighbor.second << ")" << endl;
    }

    return 0;
}
```
### Example Output

For a `3x3` matrix and cell `(2, 0)`, the output of the program will be:

<pre>
Valid neighbors:
(2, 1)
(1, 0)
</pre>

These are the valid neighboring cells of `(2, 0)` within the `3x3` matrix.
### Explanation of `dx` and `dy` Arrays

- **i = 0**: Move **right**  (`dx[0] = 0`, `dy[0] = 1`) → `(x, y + 1)`
- **i = 1**: Move **up**    (`dx[1] = -1`, `dy[1] = 0`) → `(x - 1, y)`
- **i = 2**: Move **down**  (`dx[2] = 1`, `dy[2] = 0`) → `(x + 1, y)`
- **i = 3**: Move **left**  (`dx[3] = 0`, `dy[3] = -1`) → `(x, y - 1)`





