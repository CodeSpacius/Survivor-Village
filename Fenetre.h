#ifndef FENETRE_H
#define FENETRE_H
#include "ClassCommun.h"
class Menu{
    private:
        int NombreElement;
        SDL_Surface **tabImage;
    public:
        SDL_Rect *tabpositionMin;
        SDL_Rect *tabpositionMax;
        bool *Active;
        void positionMouve(int Indice,SDL_Rect pos){
            tabpositionMax[Indice].x=tabpositionMax[Indice].x-tabpositionMin[Indice].x+pos.x;
            tabpositionMax[Indice].y=tabpositionMax[Indice].y-tabpositionMin[Indice].y+pos.y;
            tabpositionMin[Indice]=pos;
        }
        void Initialisation(char *file){
            FILE *fichier=fopen(file,"r");
            if(fichier==NULL){exit(-1);}
            fscanf(fichier,"Nombre d'element:%d\n",&NombreElement);
            while(fgetc(fichier)!='\n'){}
            //Allocation dynamique de la mémoire
            Active=(bool*)malloc(NombreElement*sizeof(bool));
            tabpositionMax=(SDL_Rect*)malloc(NombreElement*sizeof(SDL_Rect));
            tabpositionMin=(SDL_Rect*)malloc(NombreElement*sizeof(SDL_Rect));
            tabImage=(SDL_Surface**)malloc(NombreElement*sizeof(SDL_Surface*));
            //Tableau des position max et min de chaque element et Chaque image
            for(int i=0;i<NombreElement;i++){
                char tab[50];
                fscanf(fichier,"%hd:%hd-%hd:%hd-%s\n",&tabpositionMin[i].x,&tabpositionMin[i].y,&tabpositionMax[i].x,&tabpositionMax[i].y,tab);
                tabImage[i]=SDL_LoadBMP(tab);
                if(tabImage[i]==NULL){exit(-1);}
                SDL_SetColorKey(tabImage[i], SDL_SRCCOLORKEY, SDL_MapRGB(tabImage[i]->format,0,0,0));
            }
            fclose(fichier);
            //Chaque image actire
            for(int i=0;i<NombreElement;i++)
                Active[i]=false;
        }
        void BlitzMenu(SDL_Surface *Ecran){
            for(int i=0;i<NombreElement;i++)
                if(Active[i])
                    SDL_BlitSurface(tabImage[i],NULL,Ecran,&tabpositionMin[i]);
        }
        int Indice(SDL_Rect pos){
            for(int i=0;i<NombreElement;i++)
                if((tabpositionMin[i].x<=pos.x && pos.x<=tabpositionMax[i].x) && (tabpositionMin[i].y<=pos.y && pos.y<=tabpositionMax[i].y))
                    return i;
            return -1;
        }
};
class Fenetre{
    private:
        //Ecran
        SDL_Surface *Ecran;
        SDL_Rect DimensionEcran;
        SDL_Surface *fond;
        SDL_Rect posFond;
    public:
        //Sourie
        SDL_Rect sourieClick,sourieMouve;
        bool cliqueG,cliqueD;
        //Evenement
        bool changement;
        char carractere;
        bool shift,ctrl,tabulation;
        //Les fonctions
        void optionnelle(char *texte,int indice=-2){
            if(strcmp(texte,(char*)"NULL")){
                TTF_Font *police=TTF_OpenFont("rainyhearts.ttf",20);
                SDL_Color couleur={255,255,255};
                if(!strcmp(texte,(char*)"AfficherCliqueOnFenetre"))
                    fond=TTF_RenderText_Blended(police,convertRectToTabChar(sourieClick),couleur);
                else if(!strcmp(texte,(char*)"AfficherMouveOnFenetre"))
                    fond=TTF_RenderText_Blended(police,convertRectToTabChar(sourieMouve),couleur);
                else if(!strcmp(texte,(char*)"Indice"))
                    fond=TTF_RenderText_Blended(police,convertIntToTabChar(indice),couleur);
            }
            else
                fond=NULL;
        }
        void afficher(Menu M){
            if(changement){
                if(fond!=NULL){SDL_BlitSurface(fond,NULL,Ecran,&posFond);}
                M.BlitzMenu(Ecran);
            }
        }
        void Clear(){
            if(changement){
                SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format,0,0,0));
            }
        }
        void flip(){
            SDL_Flip(Ecran);
        }
        bool evenement(){
            SDL_Event event;
            SDL_WaitEvent(&event);
            changement=true;
            carractere=0;
            switch(event.type){
                case SDL_MOUSEBUTTONDOWN:
                    switch(event.button.button){
                        case SDL_BUTTON_LEFT:cliqueG=true;break;
                        case SDL_BUTTON_RIGHT:cliqueD=true;break;
                    }
                    sourieClick.x=event.button.x;sourieClick.y=event.button.y;
                break;
                case SDL_MOUSEBUTTONUP:
                    cliqueD=false;cliqueG=false;
                break;
                case SDL_MOUSEMOTION:sourieMouve.x=event.button.x;sourieMouve.y=event.button.y;break;
                case SDL_QUIT:return false;break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym){
                        case SDLK_LSHIFT:shift=false;break;
                        case SDLK_LCTRL:ctrl=false;break;
                        default:break;
                    }
                break;
                case SDL_KEYDOWN:
                    if(SDLK_a<=event.key.keysym.sym && event.key.keysym.sym<=SDLK_z){carractere=event.key.keysym.sym;}
                    if(SDLK_0<=event.key.keysym.sym && event.key.keysym.sym<=SDLK_9){carractere=event.key.keysym.sym;}
                    if(SDLK_KP0<=event.key.keysym.sym && event.key.keysym.sym<=SDLK_KP9){carractere=event.key.keysym.sym-208;}
                    switch(event.key.keysym.sym){
                        case SDLK_LSHIFT:shift=true;break;
                        case SDLK_LCTRL:ctrl=true;break;
                        case SDLK_ESCAPE:return false;break;
                        case SDLK_CAPSLOCK:if(tabulation){tabulation=false;}else{tabulation=true;}break;
                        default:break;
                    }
                break;
                default:
                    changement=false;
                break;
            }
            return true;
        }
        void Initialisation(int X,int Y){
            fond=NULL;
            SDL_WM_SetCaption("WYSM", NULL);
            DimensionEcran.x=X;DimensionEcran.y=Y;
            posFond.x=0;posFond.y=DimensionEcran.y-15;
            sourieClick.x=-1;sourieClick.y=-1;
            sourieMouve.x=-1;sourieMouve.y=-1;
            cliqueD=false;cliqueG=false;
            tabulation=false;
            ctrl=false;
            shift=false;
            Ecran=SDL_SetVideoMode(DimensionEcran.x,DimensionEcran.y,32,SDL_HWSURFACE);
        }
};
#endif

