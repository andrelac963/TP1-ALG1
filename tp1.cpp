#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Ponto
{
  double x, y;
};

struct Entrada
{
  Ponto p;
  int grau;
  vector<int> vizinhos;
};

struct Vertice
{
  int id;
  bool visitado;
  double angulo;
};

int proximo(int i, int j, vector<vector<Vertice>> &adj)
{
  int proximo;

  for (int k = 0; k < adj[j].size(); k++)
  {
    if (adj[j][k].id == i)
    {
      if (k == adj[j].size() - 1)
      {
        proximo = 0;
      }
      else
      {
        proximo = k + 1;
      }
    }
  }

  if (proximo == adj[j].size())
  {
    proximo = 0;
  }

  return proximo;
}

void DFS(int i, int j, int num_faces, vector<vector<Vertice>> &adj, vector<vector<int>> &faces)
{
  adj[i][j].visitado = true;
  faces[num_faces].push_back(i);

  int next = proximo(i, adj[i][j].id, adj);

  i = adj[i][j].id;
  j = next;

  if (!adj[i][j].visitado)
  {
    DFS(i, j, num_faces, adj, faces);
  }
}

int main()
{
  int n, m;
  vector<Entrada> grafo;

  cin >> n >> m;

  grafo.resize(n);

  for (int i = 0; i < n; i++)
  {
    cin >> grafo[i].p.x >> grafo[i].p.y >> grafo[i].grau;

    grafo[i].vizinhos.resize(grafo[i].grau);

    for (int j = 0; j < grafo[i].grau; j++)
    {
      cin >> grafo[i].vizinhos[j];
      grafo[i].vizinhos[j]--;
    }
  }

  vector<vector<Vertice>> adj;
  adj.resize(n, vector<Vertice>());

  for (int i = 0; i < n; i++)
  {
    adj[i].resize(grafo[i].grau);
    for (int j = 0; j < grafo[i].grau; j++)
    {
      adj[i][j].id = grafo[i].vizinhos[j];
      adj[i][j].visitado = false;
      adj[i][j].angulo = atan2(grafo[adj[i][j].id].p.y - grafo[i].p.y, grafo[adj[i][j].id].p.x - grafo[i].p.x);
    }
    sort(adj[i].begin(), adj[i].end(), [](Vertice a, Vertice b)
         { return a.angulo < b.angulo; });
  }

  int num_faces = 0;

  vector<vector<int>> faces;
  faces.resize(m + 2 - n);

  vector<bool> visitados(n, false);

  for (int i = 0; i < n; i++)
  {
    if (!visitados[i] && adj[i].size() != 1)
    {
      for (int j = 0; j < adj[i].size(); j++)
      {
        if (!adj[i][j].visitado)
        {
          DFS(i, j, num_faces, adj, faces);
          faces[num_faces].push_back(i);
          num_faces++;
        }
      }
      visitados[i] = true;
    }
  }

  cout << num_faces << endl;

  for (int i = 0; i < faces.size(); i++)
  {
    cout << faces[i].size() << " ";
    for (int j = 0; j < faces[i].size(); j++)
    {
      cout << faces[i][j] + 1 << " ";
    }
    cout << endl;
  }

  return 0;
}