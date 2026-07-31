#include <bits/stdc++.h>
using namespace std;

// use ordered map to store movies sorted by price in ascending order.

struct Shop {
    unordered_map<int, int> store;

    void addMovie(int movie, int price) {
        store[movie] = price;
    }

    int get_price(int movie) {
        return store.at(movie);
    }
};

struct AllRentedMovies {
    struct Data {
        int shop, movie, price;
    };

    struct Compare {
        bool operator()(const Data& o1, const Data& o2) const {
            if (o1.price != o2.price) return o1.price < o2.price;
            if (o1.shop != o2.shop) return o1.shop < o2.shop;
            return o1.movie < o2.movie;
        }
    };

    set<Data, Compare> store;

    void add_rented_movie(int shop, int movie, int price) {
        store.insert({shop, movie, price});
    }

    void remove_rented_movie(int shop, int movie, int price) {
        store.erase({shop, movie, price});
    }

    vector<vector<int>> top5_rented() {
        vector<vector<int>> out;
        for (auto [i, it] = pair{0, store.begin()}; i < 5 && it != store.end(); i++, it++) {
            out.push_back({it->shop, it->movie});
        }
        return out;
    }

};

struct MoviePrices {
    struct ShopPrice {
        int shop, price;
    };

    struct Compare {
        bool operator()(const ShopPrice& o1, const ShopPrice& o2) const {
            if (o1.price != o2.price) return o1.price < o2.price;
            return o1.shop < o2.shop;
        }
    };

    unordered_map<int, int> shopToPrice;
    set<ShopPrice, Compare> store;

    void remove_movie(int shop) {
        int price = shopToPrice[shop];
        shopToPrice.erase(shop);
        store.erase({shop, price});
    }

    void add_movie(int shop, int price) {
        shopToPrice[shop] = price;
        store.insert({shop, price});
    }

    vector<int> top5() {
        vector<int> out;
        for (auto [i, it] = pair{0, store.begin()}; it != store.end() && i < 5; i++, it++) {
            out.push_back(it->shop);
        }
        return out;
    }
};


class MovieRentingSystem {
public:
    unordered_map<int, MoviePrices> movie_prices;
    AllRentedMovies rented_movies;
    unordered_map<int, Shop> shops;

    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (auto& v : entries) {
            shops[v[0]].addMovie(v[1], v[2]);
            movie_prices[v[1]].add_movie(v[0], v[2]);
        }

    }
    
    vector<int> search(int movie) {
        return movie_prices[movie].top5();
    }
    
    void rent(int shop, int movie) {
        int price = shops.at(shop).get_price(movie);
        movie_prices.at(movie).remove_movie(shop);
        rented_movies.add_rented_movie(shop, movie, price);
    }
    
    void drop(int shop, int movie) {
        int price = shops.at(shop).get_price(movie);
        rented_movies.remove_rented_movie(shop, movie, price);
        movie_prices.at(movie).add_movie(shop, price);
    }
    
    vector<vector<int>> report() {
        return rented_movies.top5_rented();
    }
};

int main() {
    int n = 3;
    vector<vector<int>> entries = {{0, 1, 5}, {0, 2, 6}, {0, 3, 7}, {1, 1, 4}, {1, 2, 7}, {2, 1, 5}};
    MovieRentingSystem system(n, entries);
}