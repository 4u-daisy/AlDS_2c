#pragma once
#include <functional>
#include <vector>
#include <iostream>

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

/*
    summary
    Insert Sort
    /summary
*/
template <class T, class TComparator = std::less<T>>
stats InsertSort(std::vector<T>& arr)
{
    stats tmp;
    int min = 0;

    for (int i = 1; i < arr.size(); i++) {
        for (int j = i; j > 0 && TComparator()(arr[j], arr[j - 1]); j--) {
            std::swap(arr[j - 1], arr[j]);
            tmp.copy_count++;
        }
        tmp.comparison_count++;
    }
    return tmp;
}

/*
    summary
    Ѕыстра€ сортировка, алгоритмическа€ сложность ........
    middleElem - maybe change
    /summary
*/
template <class T, class TComparator = std::less <T>>
stats QuickSort(std::vector<T>& arr, int left, int right)
{
    stats tmp;
    int first = left;
    int last = right;
    T middleElem = arr[(first + last) / 2];

    do {
        while (TComparator()(arr[first], middleElem))
            first++;
        while (TComparator()(middleElem, arr[last]))
            last--;

        if (first <= last) {
            if (TComparator()(arr[last], arr[first]))
                std::swap(arr[first], arr[last]);
            first++;
            last--;
        }

    } while (first <= last);

    if (first < right)
        QuickSort(arr, first, right);
    if (left < last)
        QuickSort(arr, left, last);

    return tmp;
};

/*
    summary
    Comb Sort
    /summary
*/
template <class T, class TComparator = std::less <T>>
stats CombSort(std::vector<T>& arr) {  //расческа
    int lng = arr.size();
    stats tmp;

    float fakt = 1.2473309;  //or float fakt = 1.3;
    int step = lng - 1;

    while (step >= 1) {
        for (int i = 0; i + step < lng; ++i) {
            if (TComparator()(arr[i + step], arr[i])) {
                std::swap(arr[i], arr[i + step]);
                tmp.copy_count++;
            }
            tmp.comparison_count++;
        }
        step /= fakt;
    }

    return tmp;
}

/*
    summary
    Shell Sort
    /summary
*/
template <class T, class TComparator = std::less<T>>
stats ShellSort(std::vector<T>& data)
{
    stats stat;
    for (size_t d = data.size() / 2; d > 0; d /= 2)
    {
        for (size_t i = d; i < data.size(); ++i)
        {
            stat.comparison_count++;
            for (size_t j = i - d; j >= 0 && TComparator()(data[j+d],data[j]); j -= d)
            {
                std::swap(data[j], data[j + d]);
                //int temp = data[j];      data[j] > data[j + d]
                //data[j] = data[j + d];
                //data[j + d] = temp;
                stat.copy_count++;
            }
        }
    }
    return stat;
}

/*
    summary
    BubbleSort, const - O(N^2)
    /summary
*/
template <class T, class TComparator = std::less<T>>
stats BubbleSort(std::vector<T>& data)
{
    stats stat;
    for (size_t i = 0; i < data.size() - 1; i++)
    {
        for (size_t j = 0; j < data.size() - i - 1; j++)
        {
            stat.comparison_count++;
            if (TComparator()(data[j + 1], data[j]))
            {
                std::swap(data[j + 1], data[j]);
                //int temp = data[j + 1];
                //data[j + 1] = data[j];
                //data[j] = temp;
                stat.copy_count++;
            }
        }
    }
    return stat;
}

/*
    summary
    Two-Way Merge Sort
    /summary
*/
template <class T, class TComparator = std::less<T>>
stats TwoWayMergeSort(std::vector<T>& data)
{
    stats stat;
    std::vector<int> res(data.size());
    size_t resl = 0;
    size_t resr = res.size() - 1;
    size_t podsize = 2;
    while (true)
    {
        size_t resl = 0; // Ћева€ граница неотсортированной последовательности в res
        size_t resr = res.size() - 1; // ѕрава€ граница неотсортированной последовательности в res
        bool left = true;
        size_t vecl = 0; // »ндекс левой границы неотсортированной последовательности в data
        size_t vecr = data.size() - 1; // »ндекс правой границы неотсортированной последовательности в data
        while (vecl < vecr)
        {
            size_t i = vecl;
            size_t j = vecr;
            while (vecl <= vecr && TComparator()(data[vecl], data[vecl + 1]))
            {
                stat.comparison_count++;
                vecl++;
                podsize++;
                if (vecl == res.size() - 1) return stat;
            }
            while (vecl <= vecr && TComparator()(data[vecr], data[vecr - 1]))
            {
                stat.comparison_count++;
                vecr--;
                podsize++;
            }
            if (left)
            {
                for (size_t p = 0; p < podsize; ++p)
                {
                    if (i <= vecl)
                    {
                        if (j < vecr) // ≈сли вс€ права€ подпоследовательность уже перебрана, то поочередно записываем левую последовательность
                        {
                            res[resl] = data[i];
                            stat.copy_count++;
                            resl++;
                            i++;
                            continue;
                        }
                        else if (data[i] < data[j]) //≈сли права€ подпоследовательность не целиком рассмотрена, то нужно сравнивать
                        {
                            stat.comparison_count++;
                            res[resl] = data[i];
                            stat.copy_count++;
                            resl++;
                            i++;
                            continue;
                        }
                        else if (i == j)
                        {
                            res[resl] = data[i];
                            stat.copy_count++;
                            break;
                        }
                    }
                    if (j >= vecr)
                    {
                        if (i > vecl) // ¬с€ лева€ подпоследовательность рассмотрена
                        {
                            res[resl] = data[j];
                            stat.copy_count++;
                            resl++;
                            j--;
                            continue;
                        }
                        else if (data[j] < data[i]) //≈сли лева€ подпоследовательность не целиком рассмотрена, то нужно сравнивать
                        {
                            stat.comparison_count++;
                            res[resl] = data[j];
                            stat.copy_count++;
                            resl++;
                            j--;
                            continue;
                        }
                        else if (i == j)
                        {
                            res[resl] = data[i];
                            stat.copy_count++;
                            break;
                        }
                    }
                }
                left = !left;
            }
            else {
                for (size_t p = 0; p < podsize; ++p)
                {
                    if (i <= vecl)
                    {
                        if (j < vecr) // ≈сли вс€ права€ подпоследовательность уже перебрана, то поочередно записываем левую последовательность
                        {
                            res[resr] = data[i];
                            stat.copy_count++;
                            resr--;
                            i++;
                            continue;
                        }
                        else if (data[i] < data[j]) //≈сли права€ подпоследовательность не целиком рассмотрена, то нужно сравнивать
                        {
                            stat.comparison_count++;
                            res[resr] = data[i];
                            stat.copy_count++;
                            resr--;
                            i++;
                            continue;
                        }
                        else if (i == j)
                        {
                            res[resl] = data[i];
                            stat.copy_count++;
                            break;
                        }
                    }
                    if (j >= vecr && data[j] < data[i])
                    {
                        stat.comparison_count++;
                        if (i > vecl) // ¬с€ лева€ подпоследовательность рассмотрена
                        {
                            res[resr] = data[j];
                            stat.copy_count++;
                            resr--;
                            j--;
                            continue;
                        }
                        else if (data[j] < data[i]) //≈сли лева€ подпоследовательность не целиком рассмотрена, то нужно сравнивать
                        {
                            stat.comparison_count++;
                            res[resr] = data[j];
                            stat.copy_count++;
                            resr--;
                            j--;
                            continue;
                        }
                        else if (i == j)
                        {
                            res[resl] = data[i];
                            stat.copy_count++;
                            break;
                        }
                    }
                }
                left = !left;
            }
            vecl++;
            vecr--;
        }
        data = res;
        for (size_t k = 0; k < res.size(); k++) res[k] = 0;
    }
    return stat;
}

/*
    summary
    Shaker Sort
    /summary
*/
template <class T, class TComparator = std::less<T>>
stats ShakerSort(std::vector<T>& data) //n^2
{
    stats shaker;

    size_t beyond = data.size() - 1;
    size_t left = 0;
    size_t right = data.size() - 1;
    do {
        for (size_t i = left; i < right; i++)
        {
            shaker.comparison_count++;
            if (TComparator()(data[i+1],data[i]))
            { //data[i] > data[i + 1]
                std::swap(data[i], data[i + 1]);
                beyond = i;
                shaker.copy_count++;
            }
        }
        right = beyond;
        for (size_t i = right; i > left; i--)
        {
            shaker.comparison_count++;
            if (TComparator()(data[i], data[i-1]))
            {
                std::swap(data[i], data[i - 1]);
                beyond = i;
                shaker.copy_count++;
            }
        }
        left = beyond;
        shaker.comparison_count++;
    } while (left < right);
    return shaker;
}

/*
    summary
    Selection Sort
    /summary
*/
template <class T, class TComparator = std::less<T>>
stats SelectionSort(std::vector<T>& data) {
    for (size_t i = 0; i < data.size() - 1; i++) {
        size_t min_index = i;
        for (int j = i + 1; j < data.size(); j++) {
            if (TComparator()(data[j], data[min_index])) {
                min_index = j;
            }
        }
        std::swap(data[i], data[min_index]);
    }
}

// TO DO

void Heap_Sort(std::vector<int>& data, size_t root, size_t size, stats& heap)
{
    size_t largest = root;
    size_t l = 2 * root + 1;
    size_t r = 2 * root + 2;
    heap.comparison_count++;
    if ((l < size) && (data[l] > data[largest]))
    {
        largest = l;
        heap.copy_count++;
    }
    heap.comparison_count++;
    if ((r < size) && (data[r] > data[largest]))
    {
        largest = r;
        heap.copy_count++;
    }
    heap.comparison_count++;
    if (largest != root)
    {
        std::swap(data[root], data[largest]);
        heap.copy_count++;
        Heap_Sort(data, largest, size, heap);
    }
}
stats Heap(std::vector<int>& data) //n*log(n)
{
    stats heap;
    int size = int(data.size());
    for (int i = size / 2 - 1; i >= 0; --i)
        Heap_Sort(data, i, size, heap);
    for (int i = size - 1; i > 0; i--)
    {
        std::swap(data[i], data[0]);
        heap.copy_count++;
        Heap_Sort(data, 0, i, heap);
    }
    
    return heap;
}