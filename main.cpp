#include "ClassCommun.h"
#include "Fenetre.h"
int main(int argc,char **argv){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    //Variables
        //Fenetre gere tout les evenement de la fenetre
        Fenetre F;
        F.Initialisation(1300,600);
        //Menu de base
        Menu M;
        M.Initialisation((char*)"fichier/Texte/InitialisationMenu.txt");
        M.Active[0]=true;M.Active[1]=true;
        //Menu des objets
        Menu Objet;
        Objet.Initialisation((char*)"fichier/Texte/InitialisationObjet.txt");
        bool mouveObjet=false;
    //Boucle
    while(F.evenement()){
        F.Clear();
        F.afficher(M);
        F.afficher(Objet);
        if(M.Indice(F.sourieClick)==0 && (F.cliqueG || F.cliqueD)){
            if(Objet.Active[0])
                Objet.Active[0]=false;
            else
                Objet.Active[0]=true;
        }
        if(Objet.Active[0]){
            if((F.cliqueG || F.cliqueD)){
                if((Objet.tabpositionMax[0].x-15<=F.sourieMouve.x && F.sourieMouve.x<=Objet.tabpositionMax[0].x) && (Objet.tabpositionMin[0].y<=F.sourieMouve.y && F.sourieMouve.y<=Objet.tabpositionMin[0].y+15)){
                    Objet.Active[0]=false;
                }
                else if((Objet.tabpositionMin[0].x<=F.sourieMouve.x && F.sourieMouve.x<=Objet.tabpositionMax[0].x) && (Objet.tabpositionMin[0].y<=F.sourieMouve.y && F.sourieMouve.y<=Objet.tabpositionMin[0].y+15)){
                    mouveObjet=true;
                }
            }
            else{
                mouveObjet=false;
            }
        }
        else{
            mouveObjet=false;
        }
        if(mouveObjet){
            Objet.positionMouve(0,F.sourieMouve);
        }
        F.optionnelle((char *)"AfficherMouveOnFenetre");
        F.flip();
    }
    return 1;
}
