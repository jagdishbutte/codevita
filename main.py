from collections import deque

# Directions based on movement rule (dx, dy)
def get_next_moves(x, y, dx, dy):
    # Forward direction
    forward = (x + dx, y + dy)
    # Right (90 degrees clockwise)
    right = (x + dy, y - dx)
    # Left (90 degrees counterclockwise)
    left = (x - dy, y + dx)
    # Backward (180 degrees)
    backward = (x - dx, y - dy)
    
    return [forward, right, left, backward]

def is_valid(x, y, M, N, grid, visited):
    return 0 <= x < M and 0 <= y < N and grid[x][y] == 0 and not visited[x][y]

def bfs(grid, M, N, src, dest, move_rule):
    # Edge case: If source and destination are the same
    if src == dest:
        return 0
    
    # BFS initialization
    queue = deque([(src[0], src[1], 0)])  # (x, y, steps)
    visited = [[False for _ in range(N)] for _ in range(M)]
    visited[src[0]][src[1]] = True
    
    # BFS loop
    while queue:
        x, y, steps = queue.popleft()
        
        # Check if we've reached the destination
        if (x, y) == (dest[0], dest[1]):
            return steps
        
        # Get all possible moves from current position
        for next_x, next_y in get_next_moves(x, y, move_rule[0], move_rule[1]):
            if is_valid(next_x, next_y, M, N, grid, visited):
                visited[next_x][next_y] = True
                queue.append((next_x, next_y, steps + 1))
    
    # If no path found, return -1 (or handle based on the problem specification)
    return -1

# Input parsing
def main():
    # Grid dimensions
    M, N = map(int, input().split())
    
    # Grid data
    grid = []
    for _ in range(M):
        grid.append(list(map(int, input().split())))
    
    # Source and destination
    src = tuple(map(int, input().split()))
    dest = tuple(map(int, input().split()))
    
    # Move rule
    move_rule = tuple(map(int, input().split()))
    
    # Perform BFS to find minimum moves
    result = bfs(grid, M, N, src, dest, move_rule)
    
    # Output result without extra spaces or newlines
    print(result, end="")

# Example usage
if __name__ == "__main__":
    main()
