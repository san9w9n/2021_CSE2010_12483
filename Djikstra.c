#include <stdio.h>
 
#define INT_MAX 2147483647 // 최대 정수
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 7  // 정점의 수
#define INF 1000    // 무한대 (연결이 없는 경우)
 
int weight[MAX_VERTICES][MAX_VERTICES] = {
    {0, 28, INF, INF, INF, 10, INF},
    {28, 0, 16, INF, INF, INF, 14},
    {INF, 16, 0, 12, INF, INF, INF},
    {INF, INF, 12, 0, 22, INF, 18},
    {INF, INF, INF, 22, 0, 25, 24},
    {10, INF, INF, INF, 25, 0, INF},
    {INF, 14, INF, 18, 24, INF, 0}
};
 
int distance[MAX_VERTICES]; // 시작 정점으로부터의 최단 경로 거리
int found[MAX_VERTICES];  // 방문한 정점 표시
 
int choose(int distance[], int n, int found[])
{
  // 현재 distance 배열에서 가장 작은 가중치 값이 위치하고 있는
  // 배열의 인덱스를 찾아 반환하는 함수
 
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    
    // 최소값 min을 찾는 반복문이다.
    // 방문한 적이 없는 정점에 대해 distance배열의 값들을 비교한다.
    for (i = 0; i < n; i++)
    {
        // 방문된 적이 없는 정점이고 현재까지의 최소값 min 보다 작다면
        if (distance[i] < min && found[i] == FALSE)
        {
            min = distance[i]; // 최소값을 의미하는 min 정보를 갱신해준다.
            minpos = i; // 최소값이 등장한 해당 정점의 인덱스를 minpos에 저장한다.
        }
    }
    // distnace 배열에서 최소값이 위치하고 있는 인덱스를 반환한다.
    return minpos;
}
 
void shortest_path(int start, int n)
// start 정점부터 n 정점까지의 최단 경로를 찾는 알고리즘
{
    int i, u, w;
    
    /* 초기화 작업 */
    for (i = 0; i < n; i++)
    {
        // 시작 정점 start를 기준으로 했을 때의 가중치로
        // distance 배열을 초기화 한다.
        distance[i] = weight[start][i];
    
        // 아직 시작을 안했으므로 방문 표시의 역할을 하는
        // found 배열을 FALSE로 초기화 한다.
        found[i] = FALSE;
    }
    // 시작 정점을 선택했으니 방문여부를 TRUE로 설정한다.
    found[start] = TRUE;
    distance[start] = TRUE;
    for (i = 0; i < n - 1; i++) // 위에서 시작 정점 값을 설정했으므로 여기서는 하나를 뺀 만큼만 반복한다.
    {
        // 최소값이 있는 인덱스의 정보를 u에 저장한다.
        u = choose(distance, n, found);
        
        // 현재 distance 배열에서 가장 작은 값이 위치한 인덱스는 u이므로
        // u번 정점을 선택을 한다. 선택함과 동시에 TRUE로 값을 써주며 방문 표시를 한다.
        found[u] = TRUE;
        // 최소 가중치가 있는 정점을 집합 S에 추가한 뒤 우리는 갱신할 수 있는 정보가 있다면
        // 그 정보를 갱신해준다. 무한대 (이 PG에서는 1000)에서 정수 거리로 갱신되는 정보나
        // 긴 거리에서 짧은 거리로 갱신되는 정보나 아래의 로직이 그대로 작동한다.
        for (w = 0; w < n; w++)
        {
        // 아직 선택되어 지지 않은 정점이고
        if (found[w] == FALSE)
        {
            // 현재 그 정점까지의 거리 (distance[u]) + 정점 w까지의 거리가
            // 기존의 w정점까지의 거리보다 가깝다면 그 정보를 갱신해준다.
            if (distance[u] + weight[u][w] < distance[w])
                distance[w] = distance[u] + weight[u][w];
            
        }
        }
    }
}
 
int main()
{
    shortest_path(0, MAX_VERTICES);
    printf("%d\n",distance[MAX_VERTICES-1]);
    return 0;
}