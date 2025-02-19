#include <iostream>
#include <cmath>

void print(int size, double** matrix, double* vector) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix[i][j] << " ";
        };

        std::cout << "| " << vector[i] << "\n";
    };
    std::cout << " \n";
};

double determinant(int size, double** matrix) {
    double det = 1;
    for (int i = 0; i < size; i++) {
        int pivot = i;
        for (int j = i + 1; j < size; j++) {
            if (std::abs(matrix[j][i]) != 0) {
                pivot = j;
            }
        }

        if (i != pivot) {
            std::swap(matrix[i], matrix[pivot]);
            det = -det; 
        }

        det *= matrix[i][i];

        for (int j = i + 1; j < size; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < size; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
    if (det != 0 && !std::isnan(det)) {
        return 1;
    }
    else {
        return 0;
    };
}

double** copyMatrix(int size, double** matrix) {
    double** newMatrix = new double*[size]; 

    for (int i = 0; i < size; i++) {
        newMatrix[i] = new double[size];
        for (int j = 0; j < size; j++) {
            newMatrix[i][j] = matrix[i][j]; 
        }
    }
    return newMatrix;
};

void gauss(int size, double** matrix, double* vector) {

        for (int i = 0; i < size; i++) {
            int row = i;
            for (int k = i + 1; k < size; k++) {
                if (std::abs(matrix[k][i]) != 0) {
                row = k;
            }
        };

        std::swap(matrix[i], matrix[row]);
        std::swap(vector[i], vector[row]);

        double lead = matrix[i][i];
        for (int j = 0; j < size; j++) {
            matrix[i][j] /= lead;
            if (std::abs(matrix[i][j]) < 1e-9) matrix[i][j] = 0.0;
        }
        vector[i] /= lead;


        for (int k = 0; k < size; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < size; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
                vector[k] -= factor * vector[i];
            }
        }

        print(size, matrix, vector);
        }


        std::cout << "Решение:\n";
            for (int i = 0; i < size; i++) {
                std::cout << "x[" << i + 1 << "] = " << vector[i] << "\n";
    }
}

int main() { 
    int size;
    std::cout << "Введите размер матрицы: ";
    std::cin >> size;

    double **matrix = new double*[size];
    double *vector = new double[size];
    double **matrix_copy = matrix;

    for (int i = 0; i < size; i++){
        matrix[i] = new double[size];
    }

    std::cout << "Введите коэффициенты системы уравнений (построчно):\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cin >> matrix[i][j];
        }
        std::cin >> vector[i];
    }

    std::cout << "\nИсходная матрица:\n";
    print(size, matrix, vector);

    if (determinant(size, copyMatrix(size, matrix))) {
        gauss(size, matrix, vector);
    }
    else {
        std::cout << "Определитель матрицы равен 0";
    }

    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] vector;

    return 0;
}
