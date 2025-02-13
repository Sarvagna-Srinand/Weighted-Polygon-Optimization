# Weighted Polygon Optimization

## Problem Statement

Given a set of points with associated weights (positive and negative), the goal is to:
- Construct a polygon that maximizes the sum of weights of enclosed points
- Ensure the polygon has at most 1000 vertices
- Account for points forming clusters based on adjacency (shared sides)

## Approach

Our solution uses a combination of cluster analysis and dynamic programming:

### Cluster Analysis
1. **Cluster Identification**
   - Identify positive clusters (connected points with positive weights)
   - Identify holes (clusters of negative weight points)
   - Map relationships between positive clusters and holes

2. **Base Solution**
   - Initially include all positive clusters in the polygon
   - Calculate total vertex count from positive clusters
   - Identify if vertex reduction is needed (if count > 1000)

3. **Hole Analysis**
   - Analyze each hole for potential inclusion
   - Including a hole can:
     - Reduce total vertex count by merging boundaries
     - Add negative weight to the total sum
     - Potentially simplify the polygon shape

### Optimization Strategy
- Knapsack-style Dynamic Programming approach to optimize hole selection
- Objective function considers:
  - Reduction in vertex count by including the hole
  - Weight penalty from negative points
  - Impact on overall polygon structure

## Implementation Details

### Dynamic Programming Solution
- **DP State Definition**
  - State: (current_vertices, selected_holes)
  - Transitions: Include/exclude each candidate hole

- **Constraints**
  - Final vertex count ≤ 1000
  - Maximize total weight

### Solution Steps
1. Calculate base metrics for positive clusters
2. Identify candidate holes for inclusion
3. Apply DP to select optimal set of holes
4. Construct final polygon boundary

### Polygon Construction
Our polygon generator takes a compressed Boolean grid as input and constructs a continuous shape by:
- Connecting all points marked as true using narrow tubes
- Ensuring tubes do not occupy any false grid spaces
- Eliminating holes by extending connections to enclose outer boundaries

### Checker
Validates that:
1. Number of edges ≤ 1000
2. No two edges intersect
3. Exactly 2 edges incident on each vertex
4. All edges are parallel to axes
5. All vertices lie on a single cycle of edges

### Alternative Approach: Column-Based Optimization
- Work directly with original grid values
- Maintain column-wise sums
- Select optimal height for each column
- Choose top 250 columns based on maximum suffix sums

## Time Complexity
- Cluster identification: O(N) where N is number of points
- DP solution: O(H * V) where:
  - H = number of holes
  - V = number of vertices to reduce
- Column-based approach: O(N * M) for column sums, O(M log M) for selection

## Results and Benefits
- Achieves vertex count within 1000-vertex limit
- Maximizes total weight of included points
- Optimizes polygon shape for given constraints
- Efficient solution through DP approach

## Running Instructions

To run the solution:

1. Make sure you have Python installed on your system
2. Clone this repository:
   ```
   git clone https://github.com/your-repo/kriti25-optimization.git
   cd kriti25-optimization
   ```

3. Run the Python script:
        python run.py
   ```
   python optimize_polygon.py [input_file] [output_file]
   ```
   
   Where:
   - `input_file` is the path to the input file containing the point grid
   - `output_file` is the path where the polygon solution will be saved

### Input Format
The input file should contain:
- First line: Two integers N and M (grid dimensions)
- Next N lines: M space-separated integers representing weights of points

### Output Format
The output file will contain:
- First line: Number of vertices in the polygon
- Next V lines: Coordinates of each vertex in clockwise order
