#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Ativo {
    string ticket;
    int quantidade;
    double precoMedio;
};

vector<Ativo> carteira;

int buscaBinaria(vector<Ativo> &carteira, const string &ticket, int inicio, int fim) {
    if (inicio > fim) return -1;

    int meio = (inicio + fim) / 2;
    if (carteira[meio].ticket == ticket) {
        return meio;
    } else if (carteira[meio].ticket > ticket) {
        return buscaBinaria(carteira, ticket, inicio, meio - 1);
    } else {
        return buscaBinaria(carteira, ticket, meio + 1, fim);
    }
}

void registrarCompra() {
    string ticket;
    int quantidade;
    double preco;

    cout << "Informe o ticket da empresa: ";
    cin >> ticket;
    cout << "Informe a quantidade comprada: ";
    cin >> quantidade;
    cout << "Informe o valor do ativo no momento da compra: ";
    cin >> preco;

    int index = buscaBinaria(carteira, ticket, 0, carteira.size() - 1);

    if (index != -1) {
        
        Ativo &ativo = carteira[index];
        ativo.precoMedio = ((ativo.precoMedio * ativo.quantidade) + (preco * quantidade)) / (ativo.quantidade + quantidade);
        ativo.quantidade += quantidade;
    } else {

        Ativo novoAtivo = {ticket, quantidade, preco};
        carteira.push_back(novoAtivo);
        sort(carteira.begin(), carteira.end(), [](const Ativo &a, const Ativo &b) {
            return a.ticket < b.ticket;
        });
    }

    cout << "Compra registrada com sucesso!" << endl;
}
void registrarVenda() {
    string ticket;
    int quantidade;
    double preco;

    cout << "Informe o ticket da empresa: ";
    cin >> ticket;
    cout << "Informe a quantidade vendida: ";
    cin >> quantidade;

    int index = buscaBinaria(carteira, ticket, 0, carteira.size() - 1);

    if (index != -1 && carteira[index].quantidade >= quantidade) {
        carteira[index].quantidade -= quantidade;
        cout << "Venda registrada com sucesso!" << endl;
    } else {
        cout << "Erro: quantidade insuficiente ou ativo nao encontrado!" << endl;
    }
}

void verSaldo() {
    string ticket;
    cout << "Informe o ticket do ativo: ";
    cin >> ticket;

    int index = buscaBinaria(carteira, ticket, 0, carteira.size() - 1);

    if (index != -1) {
        Ativo &ativo = carteira[index];
        cout << "Saldo do ativo " << ativo.ticket << ": " << ativo.quantidade << " ações, preco medio: R$" << ativo.precoMedio << endl;
    } else {
        cout << "Ativo não encontrado!" << endl;
    }
}

void listarPatrimonio() {
    cout << "Lista de ativos na carteira:" << endl;
    for (const Ativo &ativo : carteira) {
        cout << "Ticket: " << ativo.ticket << ", Quantidade: " << ativo.quantidade << ", Preco Medio: R$" << ativo.precoMedio << endl;
    }
}

void menu() {
    int opcao;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Registrar Compra\n";
        cout << "2. Registrar Venda\n";
        cout << "3. Ver Saldo de um Ativo\n";
        cout << "4. Listar Patrimonio\n";
        cout << "5. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                registrarCompra();
                break;
            case 2:
                registrarVenda();
                break;
            case 3:
                verSaldo();
                break;
            case 4:
                listarPatrimonio();
                break;
            case 5:
                cout << "Saindo do sistema..." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
        }

    } while (opcao != 5);
}

int main() {
    menu();
    return 0;
}
