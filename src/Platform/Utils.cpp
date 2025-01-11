#include "Utils.h"

// Funkcja pomocnicza sprawdzająca, czy punkt P leży wewnątrz trójkąta ABC
bool isPointInTriangle(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f P) {
    float w1 = (A.x * (C.y - A.y) + (P.y - A.y) * (C.x - A.x) - P.x * (C.y - A.y)) /
        ((B.y - A.y) * (C.x - A.x) - (B.x - A.x) * (C.y - A.y));
    float w2 = (P.y - A.y - w1 * (B.y - A.y)) / (C.y - A.y);
    return w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1;
}

// Funkcja sprawdzająca, czy trójkąt (A, B, C) jest uchem
bool isEar(const std::vector<sf::Vector2f>& vertices, int i, int prev, int next) {
    sf::Vector2f A = vertices[prev];
    sf::Vector2f B = vertices[i];
    sf::Vector2f C = vertices[next];

    // Sprawdź, czy trójkąt jest wypukły
    float crossProduct = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
    if (crossProduct <= 0)
    {
        return false; // Trójkąt jest wklęsły, nie jest uchem
    }

    // Sprawdź, czy inne wierzchołki leżą wewnątrz trójkąta
    for (size_t j = 0; j < vertices.size(); j++) {
        if (j != i && j != prev && j != next && isPointInTriangle(A, B, C, vertices[j])) {
            return false; // Trójkąt zawiera inne wierzchołki, nie jest uchem
        }
    }
    return true; // Trójkąt jest uchem
}

// Funkcja do triangulacji wielokąta metodą Ear Clipping
std::vector<Triangle> triangulate(std::vector<sf::Vector2f>& vertices) {
    std::vector<Triangle> triangles;
    std::vector<int> indices(vertices.size());
    for (int i = 0; i < vertices.size(); i++) {
        indices[i] = i;
    }

    int n = vertices.size();
    while (n > 3) {
        bool earFound = false;

        for (int i = 0; i < n; i++) {
            int prev = (i + n - 1) % n;
            int next = (i + 1) % n;

            if (isEar(vertices, indices[i], indices[prev], indices[next])) {
                // Dodaj trójkąt do listy meshu
                triangles.push_back({ vertices[indices[prev]], vertices[indices[i]], vertices[indices[next]] });

                // Usuń ucho z listy
                indices.erase(indices.begin() + i);
                n--;
                earFound = true;
                break;
            }
        }

        // Jeśli nie znaleziono ucha, zakończ (uniknięcie nieskończonej pętli)
        if (!earFound) break;
    }

    // Dodaj ostatni pozostały trójkąt
    if (n == 3) {
        triangles.push_back({ vertices[indices[0]], vertices[indices[1]], vertices[indices[2]] });
    }

    return triangles;
}

void Explode(char ExplodeChar, std::string String, std::vector<std::string>& Items)
{
	char ch;
	std::string CurrentString = "";
	Items.clear();
	for (size_t i = 0; i < String.length(); i++)
	{
		ch = String[i];
		if (ch == ExplodeChar)
		{
			Items.push_back(CurrentString);
			CurrentString = "";
		}
		else
		{
			CurrentString += ch;
		}
	}
	if (CurrentString.length() > 0)
	{
		Items.push_back(CurrentString);
	}
}
