#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <cstring>
#include <cstdio>

using namespace std;

// Pentru generarea de numere in metode si constructor
template <typename X>
X rnd(X n)
{
    return (rand()%n + 1);
}

// Clasa care prelucreaza datele pentru cast si costuri
class ActorsCast
{
    private:
        float castNumber = 0; //numarul total al oamenilor implicati
        int autocare;         //autocarele necesare
        int actorsCast = 0;   //actorii si figurantii

    public:
        //contructor care genereaza fisierul cerut la rularea programului
        ActorsCast()
        {
            ifstream f("original_cast.csv"); //fisier care contine cast-ul initial
            ofstream g("cast_extended.csv"); //fisierul creat dupa generarea random a figurantilor

            srand(time(NULL));

            int i, n, m;
            string line;

            //vectori de nume si prenume pentru figuranti random
            string lastNames[] = {"Blossom", "Prince", "Flores", "Miro", "Sandro", "Hart", "Grecu", "Antoine", "Bliss", "Dragu", "Voinea"};
            string firstNames[] = {"Mary", "Annabelle", "Henry", "Harry", "William", "Claudia", "Francesca", "Elizabeth", "Michael", "Evan", "Christopher", "Clara", "Emily", "Cassidy", "Kyle", "Valeria"};

            //salvarea persoanelor din fisierul original in noul fisier
            while (!f.eof())
            {
                getline(f, line);
                g << line << endl;
                (this -> castNumber)++;
            }

            //generarea figurantilor si salvarea acestora in fisier
            for (i = 0; i < 132; i++)
            {
                g << firstNames[rnd<int>(15)] << " " << lastNames[rnd<int>(10)] << ";" << "cast extra;" << endl;
                (this -> castNumber)++;
            }

            f.close();
            g.close();
        }

        //metoda pentru calculul autocarelor necesare
        void autocareNecesare()
        {
            this -> autocare = ceil(this -> castNumber / 50);
            throw this -> autocare;
        }

        //metoda de cautare si salvare a numarului de actori si figuranti
        void numberCastActors()
        {
            ifstream f("original_cast.csv");
            string word;

            //cautarea actorilor
            while (!f.eof())
            {
                getline(f, word, ';');
                if (!word.compare("actor"))
                    (this -> actorsCast)++;
            }
            //adaugarea figurantilor, stiindu-se numarul acestora
            this -> actorsCast = this -> actorsCast + 132;

            f.close();
        }

        //generarea fisierului de costuri in romana folosind ca moneda 'leul'
        void costTotal(int zile)
        {
            ifstream g("costuri.csv");
            ofstream f("intermediate.csv");
            srand(time(NULL));

            int costAutocare, costMeniu = 0, i, j, cam2, cam3 = 44, costMachiaj = 0, costCastel = 0;
            int machiaje[] = {230, 555, 345, 157, 55}; //preturi la machiaj per zi per persoana
            int pretMeniu[] ={40, 33, 46};             //preturi pe meniuri per zi per persoana
            int acs = (3 + 15 + 3.2)* zile, cost = 10000;
            //acs = apa + cafea + suc per sedere, calculand folosind media zilnica de consum
            //cam3 = camerele de 3 persoane rezervate figurantilor

            costAutocare = (this -> autocare) * 5680; // cost inchiriere autocare

            //calcul cost machiaj per total sedere, calculand random pentru fiecare zi de filmare
            for (j = 0; j < zile; j++)
            {
                i = 0;
                while (i < this -> actorsCast)
                {
                    costMachiaj = costMachiaj + machiaje[rnd<int>(4)];
                    i++;
                }
            }

            //calcul cost meniuri per zi
            i = 0;
            while (i < this -> castNumber)
            {
                costMeniu = costMeniu + pretMeniu[rnd<int>(2)];
                i++;
            }

            //numarul de camere de 2 persoane pentru cast-ul initial
            cam2 = ceil((this -> castNumber - 132) / 2);

            //calcul inchiriere castel per total zile de filmare
            for (i = 1; i <= zile; i++)
            {
                costCastel = costCastel + cost;
                if (i % 10 == 0)
                    cost = cost - 0.02*cost;
            }

            //adaugarea fiecarei iterari de zile in acelasi fisier pentru comparatie
            string line;
            while(!g.eof())
            {
                getline(g, line);
                f << line << endl;
            }

            f << "Costuri pe " << zile << " zile (in lei);" << endl;
            f << "Transport;" << costAutocare * 2 << ";" << endl;
            f << "Cazare;" << (cam2 * 350 + cam3 * 420) * (zile - 1) << ";" << endl;
            f << "Machiaj;" << costMachiaj * zile << ";" << endl;
            f << "Mancare si apa;" << costMeniu * zile + acs << ";" << endl;
            f << "Inchiriere spatiu;" << costCastel << ";" << endl;

            f.close();
            g.close();

            remove("costuri.csv");
            rename("intermediate.csv", "costuri.csv");
        }

        //generarea fisierului de costuri in engleza folosind ca moneda '$'
        void costTotal(int zile, char c)
        {
            ifstream g("total_cost.csv");
            ofstream f("intermediate.csv");
            srand(time(NULL));

            int costAutocare, costMeniu = 0, i, j, cam2, cam3 = 44, costMachiaj = 0, costCastel = 0;
            int machiaje[] = {230, 555, 345, 157, 55};
            int pretMeniu[] ={40, 33, 46};
            int acs = (3 + 15 + 3.2)* zile, cost = 10000;
            float dolar = 0.22; // 1 leu = 0.22 dolari

            costAutocare = (this -> autocare) * 5680;

            for (j = 0; j < zile; j++)
            {
                i = 0;
                while (i < this -> actorsCast)
                {
                    costMachiaj = costMachiaj + machiaje[rnd<int>(4)];
                    i++;
                }
            }

            i = 0;
            while (i < this -> castNumber)
            {
                costMeniu = costMeniu + pretMeniu[rnd<int>(2)];
                i++;
            }

            cam2 = ceil((this -> castNumber - 132) / 2);

            for (i = 1; i <= zile; i++)
            {
                costCastel = costCastel + cost;
                if (i % 10 == 0)
                    cost = cost - 0.02*cost;
            }

            string line;
            while(!g.eof())
            {
                getline(g, line);
                f << line << endl;
            }

            f << "Costs for " << zile << " days (in $);" << endl;
            f << "Transport;" << costAutocare * 2 * dolar << "$;" << endl;
            f << "Housing;" << int((cam2 * 350 + cam3 * 420) * (zile - 1) * dolar) << "$;" << endl;
            f << "Make up;" << int(costMachiaj * zile * dolar) << "$;" << endl;
            f << "Food and water;" << int((costMeniu * zile + acs) * dolar) << "$;" << endl;
            f << "Space renting;" << int(costCastel * dolar) << "$;" << endl;

            f.close();
            g.close();

            remove("total_cost.csv");
            rename("intermediate.csv", "total_cost.csv");
        }
        ~ActorsCast()
        {
            cout << "Deleting default constructor." << endl;
        }
};

class Meniu
{
    private:
        string supaVegetarieni[10] = {"Supa gazpacho", "Supa cu morcov, mazare si gnocchi din naut", "Supa cu telina si broccoli", "Supa cu dovleac", "Supa-crema cu fasole si cartof dulce", "Ciorba de fasole", "Supa-crema de legume cu crutoane", "Supa de legume cu fidea", "Ciorba de varza", "Mancare de mazare"};
        string supaFlexitarieni[9] = {"Supa cu morcov, mazare si gnocchi din naut", "Supa cu telina si broccoli", "Supa cu ciuperci, cartofi si ton", "Supa-crema cu fasole si cartof dulce", "Ciorba de fasole", "Supa-crema de legume cu crutoane", "Supa de legume cu fidea", "Ciorba de varza", "Mancare de mazare"};
        string supaCiorba[11] = {"Supa-crema cu fasole si cartof dulce", "Ciorba de fasole", "Supa-crema de legume cu crutoane", "Supa de legume cu fidea", "Ciorba de varza", "Ciorba de pui", "Ciorba de vacuta", "Ciorba de perisoare", "Ciorba taraneasca de pui", "Ciorba de porc", "Mancare de mazare"};
        string felPrincipalV[15] = {"Dovleac cremos", "Orez cu spanac, oua si branza de capra", "Paste cu sos de avocado", "Paste cu branza de vaci si legume inabusite", "Falafel la cuptor cu hummus", "Paste cu sos cremos de busuioc", "Paste cu zucchini", "Risotto cu zucchini", "Salata cu rucola si avocado", "Piure de cartofi", "Piure de morcovi cu ardei copti", "Vinete umplute", "Fasole batuta", "Tocanita de ciuperci", "Sufle de legume"};
        string felPrincipalF[24] = {"Omleta cu ton", "Tofu cu branza, cuscus si ton", "Orez cu spanac, oua si branza de capra", "Paste cu sos de avocado si ton", "Paste cu branza de vaci si legume inabusite", "Falafel la cuptor cu hummus", "Paste cu sos cremos de busuioc", "Paste cu zucchini si ton", "Risotto cu zucchini si ton", "Salata cu rucola si avocado", "Piure de cartofi", "Piure de morcovi cu ardei copti", "Vinete umplute", "Fasole batuta", "Tocanita de ciuperci", "Sufle de legume", "Orez cu patrunzel, limeta si ton", "Hrisca cu spanac, ciuperci, branza si ton", "Drob cu ton", "Salata cu paste, legume si ton", "Orez cu ton si porumb", "Somon cu bulgur in sos Teriyaki", "Tort sarat cu spanac si somon", "Somon fript cu cipsuri din legume si sos de iaurt cu usturoi"};
        string felPrincipal[24] = {"Orez cu spanac, oua si branza de capra", "Paste cu sos de avocado", "Paste cu branza de vaci si legume inabusite", "Paste cu sos cremos de busuioc", "Salata cu rucola si avocado", "Piure de cartofi", "Piure de morcovi cu ardei copti", "Vinete umplute", "Fasole batuta", "Tocanita cu ciuperci", "Sufle de legume", "Pui cu sos cremos de spanac si lamaie", "Chiftelute marinate", "Ficatei de pui", "Snitel de pui", "Rulada de pui/curcan", "Pulpe de pui la cuptor", "Pui cu ardei la cuptor", "Ceafa de porc cu legume la cuptor"};
        string desert[16] = {"Prajitura cu miere", "Cheesecake cu cirese", "Briose cu morcov", "Budinca cu orez, lapte, vanilie si mango", "Cheesecake cu zmeura", "Prajitura cu zmeura", "Prajitura cu merisoare", "Prajitura cu banane", "Mousse cu ciocolata", "Prajitura cu branza de vaci", "Chec", "Clatite cu dulceata", "Tiramisu cu fructe", "Briose cu fructe uscate", "Placinta cu mere", "Tort de biscuiti"};

        string esupaVegetarieni[10] = {"Gazpacho soup", "Carrot, pea and chickpea gnocchi soup", "Celery and broccoli soup", "Pumpkin soup", "Cream soup with beans and sweet potato", "Bean soup", "Vegetable cream soup with croutons", "Vegetable soup with noodles", "Cabbage soup", "Pea soup"};
        string esupaFlexitarieni[9] = {"Carrot, pea and chickpea gnocchi soup", "Celery and broccoli soup", "Soup with mushrooms, potatoes and tuna", "Cream soup with beans and sweet potato", "Bean soup", "Vegetable cream soup with croutons", "Vegetable soup with noodles", "Cabbage soup", "Pea soup"};
        string esupaCiorba[11] = {"Cream soup with beans and sweet potato", "Bean soup", "Vegetable cream soup with croutons", "Vegetable soup with noodles", "Cabbage soup", "Chicken soup", "Beef soup", "Meatball soup", "Peasant chicken soup", "Pork soup", "Pea soup"};
        string efelPrincipalV[15] = {"Creamy pumpkin", "Rice with spinach, eggs and goat cheese", "Pasta with avocado sauce", "Pasta with cottage cheese and stewed vegetables", "Baked falafel with hummus", "Pasta with creamy basil sauce", "Pasta with zucchini", "Risotto with zucchini", "Salad with arugula and avocado", "Mashed potatoes", "Carrot puree with baked peppers", "Stuffed eggplant", "Beaten beans", "Mushroom stew", "Vegetable souffle"};
        string efelPrincipalF[24] = {"Omelette with tuna", "Tofu with cheese, couscous and tuna", "Rice with spinach, eggs and goat cheese", "Pasta with avocado sauce and tuna", "Pasta with cottage cheese and stewed vegetables", "Baked falafel with hummus", "Pasta with creamy basil sauce", "Pasta with zucchini and tuna", "Risotto with zucchini and tuna", "Salad with arugula and avocado", "Mashed potatoes", "Carrot puree with baked peppers", "Stuffed eggplant", "Beaten beans", "Mushroom stew", "Vegetable souffle", "Rice with parsley, lime and tuna", "Buckwheat with spinach, mushrooms, cheese and tuna", "Drob with tuna", "Salad with pasta, vegetables and tuna", "Rice with tuna and corn", "Salmon with bulgur in Teriyaki sauce", "Savory cake with spinach and salmon", "Roasted salmon with vegetable chips and garlic yogurt sauce"};
        string efelPrincipal[24] = {"Rice with spinach, eggs and goat cheese", "Pasta with avocado sauce", "Pasta with cottage cheese and stewed vegetables", "Pasta with creamy basil sauce", "Salad with arugula and avocado", "Mashed potatoes", "Carrot puree with baked peppers", "Stuffed eggplant", "Beaten beans", "Mushroom stew", "Vegetable souffle", "Creamy spinach lemon chicken", "Marinated meatballs", "Chicken livers", "Chicken schnitzel", "Chicken/turkey roll", "Baked chicken thighs", "Chicken with peppers in the oven", "Pork neck with vegetables in the oven"};
        string edesert[16] = {"Honey cake", "Cheesecake with cherries", "Carrot muffins", "Pudding with rice, milk, vanilla and mango", "Cheesecake with raspberries", "Raspberry cake", "Cranberry cake", "Banana cake", "Chocolate mousse", "Cottage cheese cake", "Cake", "Pancakes with jam", "Tiramisu with fruit", "Muffins with dried fruit", "Apple pie", "Cookie cake"};

    public:
        //metoda de creare a unui meniu in functie de zilele de sedere in engleza
        void creareMeniu(int zile, char c)
        {
            ofstream f("Menu.csv");

            srand(time(NULL));

            int i, j, n;
            n = zile / 3;

            //crearea o data la trei zile a unui meniu pentru fiecare categorie de dieta
            for (i = 0; i < 3*n; i = i + 3)
            {
                f << "Days " << i + 1 << " - " << i + 3 << endl;
                f << "Vegetarian menu" << endl;
                f << "Soup;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << esupaVegetarieni[rnd<int>(9)] << endl;
                    else f << esupaVegetarieni[rnd<int>(9)] << ";";

                f << "Main dish;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << efelPrincipalV[rnd<int>(14)] << endl;
                    else f << efelPrincipalV[rnd<int>(14)] << ";";

                f << "Desert;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << edesert[rnd<int>(15)] << endl;
                    else f << edesert[rnd<int>(15)] << ";";

                f << "Flexitarian menu" << endl;
                f << "Soup;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << esupaFlexitarieni[rnd<int>(8)] << endl;
                    else f << esupaFlexitarieni[rnd<int>(8)] << ";";

                f << "Main dish;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << efelPrincipalF[rnd<int>(23)] << endl;
                    else f << efelPrincipalF[rnd<int>(23)] << ";";

                f << "Desert;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << edesert[rnd<int>(15)] << endl;
                    else f << edesert[rnd<int>(15)] << ";";

                f << "Menu fit to eat anything" << endl;
                f << "Soup;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << esupaCiorba[rnd<int>(10)] << endl;
                    else f << esupaCiorba[rnd<int>(10)] << ";";

                f << "Main dish;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << efelPrincipal[rnd<int>(23)] << endl;
                    else f << efelPrincipal[rnd<int>(23)] << ";";

                f << "Desert;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << edesert[rnd<int>(15)] << endl;
                    else f << edesert[rnd<int>(15)] << ";";
            }

            //crearea unui meniu pentru ultimele 2 zile de filmari
            if (zile - 3*n == 2)
            {
                f << "Days " << n + 1 << " - " << zile << endl;
                f << "Vegetarian menu" << endl;
                f << "Soup;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << esupaVegetarieni[rnd<int>(9)] << endl;
                    else f << esupaVegetarieni[rnd<int>(9)] << ";";

                f << "Main dish;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << efelPrincipalV[rnd<int>(14)] << endl;
                    else f << efelPrincipalV[rnd<int>(14)] << ";";

                f << "Desert;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << edesert[rnd<int>(15)] << endl;
                    else f << edesert[rnd<int>(15)] << ";";

                f << "Flexitarian menu" << endl;
                f << "Soup;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << esupaFlexitarieni[rnd<int>(8)] << endl;
                    else f << esupaFlexitarieni[rnd<int>(8)] << ";";

                f << "Main dish;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << efelPrincipalF[rnd<int>(23)] << endl;
                    else f << efelPrincipalF[rnd<int>(23)] << ";";

                f << "Desert;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << edesert[rnd<int>(15)] << endl;
                    else f << edesert[rnd<int>(15)] << ";";

                f << "Menu fit to eat anything" << endl;
                f << "Soup;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << esupaCiorba[rnd<int>(10)] << endl;
                    else f << esupaCiorba[rnd<int>(10)] << ";";

                f << "Main dish;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << efelPrincipal[rnd<int>(23)] << endl;
                    else f << efelPrincipal[rnd<int>(23)] << ";";

                f << "Desert;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << edesert[rnd<int>(15)] << endl;
                    else f << edesert[rnd<int>(15)] << ";";
            }
            else if (zile - 3*n == 1) //crearea unui meniu pentru ultima zi de filmare
            {
                f << "Day " << zile << endl;

                f << "Vegetarian menu" << endl;
                f << "Soup;" << esupaVegetarieni[rnd<int>(9)] << endl;
                f << "Main dish;" << efelPrincipalV[rnd<int>(14)] << endl;
                f << "Desert;" << edesert[rnd<int>(15)] << endl;

                f << "Flexitarian menu" << endl;
                f << "Soup;" << esupaFlexitarieni[rnd<int>(8)] << endl;
                f << "Main dish;" << efelPrincipalF[rnd<int>(23)] << endl;
                f << "Desert;" << edesert[rnd<int>(15)] << endl;

                f << "Menu fit to eat anything" << endl;
                f << "Soup;" << esupaCiorba[rnd<int>(10)] << endl;
                f << "Main dish;" << efelPrincipal[rnd<int>(23)] << endl;
                f << "Desert;" << edesert[rnd<int>(15)] << endl;
            }

            f.close();
            throw "The menu was created.";
        }

        //metoda de creare a unui meniu in functie de zilele de sedere in romana
        void creareMeniu(int zile)
        {
            ofstream f("Meniu.csv");

            srand(time(NULL));

            int i, j, n;
            n = zile / 3;

            for (i = 0; i < 3*n; i = i + 3)
            {
                f << "Zilele " << i + 1 << " - " << i + 3 << endl;
                f << "Meniu vegetarian" << endl;
                f << "Supa / Ciorba;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << supaVegetarieni[rnd<int>(9)] << endl;
                    else f << supaVegetarieni[rnd<int>(9)] << ";";

                f << "Fel principal;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << felPrincipalV[rnd<int>(14)] << endl;
                    else f << felPrincipalV[rnd<int>(14)] << ";";

                f << "Desert;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << desert[rnd<int>(15)] << endl;
                    else f << desert[rnd<int>(15)] << ";";

                f << "Meniu flexitarian" << endl;
                f << "Supa / Ciorba;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << supaFlexitarieni[rnd<int>(8)] << endl;
                    else f << supaFlexitarieni[rnd<int>(8)] << ";";

                f << "Fel principal;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << felPrincipalF[rnd<int>(23)] << endl;
                    else f << felPrincipalF[rnd<int>(23)] << ";";

                f << "Desert;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << desert[rnd<int>(15)] << endl;
                    else f << desert[rnd<int>(15)] << ";";

                f << "Meniu apti sa manance orice" << endl;
                f << "Supa / Ciorba;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << supaCiorba[rnd<int>(10)] << endl;
                    else f << supaCiorba[rnd<int>(10)] << ";";

                f << "Fel principal;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << felPrincipal[rnd<int>(23)] << endl;
                    else f << felPrincipal[rnd<int>(23)] << ";";

                f << "Desert;";
                for (j = 0; j < 3; j++)
                    if (j == 2)
                        f << desert[rnd<int>(15)] << endl;
                    else f << desert[rnd<int>(15)] << ";";
            }

            if (zile - 3*n == 2)
            {
                f << "Zilele " << n + 1 << " - " << zile << endl;
                f << "Meniu vegetarian" << endl;
                f << "Supa / Ciorba;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << supaVegetarieni[rnd<int>(9)] << endl;
                    else f << supaVegetarieni[rnd<int>(9)] << ";";

                f << "Fel principal;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << felPrincipalV[rnd<int>(14)] << endl;
                    else f << felPrincipalV[rnd<int>(14)] << ";";

                f << "Desert;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << desert[rnd<int>(15)] << endl;
                    else f << desert[rnd<int>(15)] << ";";

                f << "Meniu flexitarian" << endl;
                f << "Supa / Ciorba;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << supaFlexitarieni[rnd<int>(8)] << endl;
                    else f << supaFlexitarieni[rnd<int>(8)] << ";";

                f << "Fel principal;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << felPrincipalF[rnd<int>(23)] << endl;
                    else f << felPrincipalF[rnd<int>(23)] << ";";

                f << "Desert;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << desert[rnd<int>(15)] << endl;
                    else f << desert[rnd<int>(15)] << ";";

                f << "Meniu apti sa manance orice" << endl;
                f << "Supa / Ciorba;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << supaCiorba[rnd<int>(10)] << endl;
                    else f << supaCiorba[rnd<int>(10)] << ";";

                f << "Fel principal;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << felPrincipal[rnd<int>(23)] << endl;
                    else f << felPrincipal[rnd<int>(23)] << ";";

                f << "Desert;";
                for (j = 0; j < 2; j++)
                    if (j == 1)
                        f << desert[rnd<int>(15)] << endl;
                    else f << desert[rnd<int>(15)] << ";";
            }
            else if (zile - 3*n == 1)
            {
                f << "Ziua " << zile << endl;

                f << "Meniu vegetarian" << endl;
                f << "Supa / Ciorba;" << supaVegetarieni[rnd<int>(9)] << endl;
                f << "Fel principal;" << felPrincipalV[rnd<int>(14)] << endl;
                f << "Desert;" << desert[rnd<int>(15)] << endl;

                f << "Meniu flexitarian" << endl;
                f << "Supa / Ciorba;" << supaFlexitarieni[rnd<int>(8)] << endl;
                f << "Fel principal;" << felPrincipalF[rnd<int>(23)] << endl;
                f << "Desert;" << desert[rnd<int>(15)] << endl;

                f << "Meniu apti sa manance orice" << endl;
                f << "Supa / Ciorba;" << supaCiorba[rnd<int>(10)] << endl;
                f << "Fel principal;" << felPrincipal[rnd<int>(23)] << endl;
                f << "Desert;" << desert[rnd<int>(15)] << endl;
            }
            f.close();
            throw "Meniul a fost creat.";
        }
};

int main()
{
    ActorsCast a;
    int c;
    try
    {
        a.numberCastActors();
        a.autocareNecesare();
    }
    catch (int msg)
    {
        cout << "Avem nevoie de " << msg << " autocare. / We need " << msg << " buses." << endl;
    }

    cout << "Sa vedem cate zile. Daca nu, apasa 'x' in orice moment. / Lets see how many days. If not, press 'x' at any time." << endl;
    cout << "Scrie numarul de zile al sederii / Write the number of days for the stay: ";
    cin >> c;
    while (!cin.fail())
    {
        if (!cin.fail())
            {
                a.costTotal(c);
                a.costTotal(c, 'e');
            }
        cout << "Scrie numarul de zile al sederii / Write the number of days for the stay: ";
        cin >> c;
    }
    cin.clear();
    cin.ignore(1);

    Meniu b;

    cout << "Pentru cate zile sa generam meniul? / For how many days to generate a menu?\nNumarul de zile / Number of days: ";
    cin >> c;
    //block-uri try-catch pentru feedback
    try
    {
        b.creareMeniu(c);
    }
    catch (const char* msg)
    {
        cout << msg << " / ";
    }

    try
    {
        b.creareMeniu(c, 'e');
    }
    catch (const char* msg)
    {
        cout << msg << endl;
    }

    return 0;
}
