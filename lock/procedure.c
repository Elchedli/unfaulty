
void enigme1(SDL_Surface *screen,SDL_Event event){
    serrure lockpick,lock;
    SDL_Surface *screen,*yaru,*rotateimage;
    SDL_Event event;
    SDL_Rect rec;
    lockpick.image = IMG_Load("/home/shidono/Desktop/godsake/pics/lock.png");
    lock.image = IMG_Load("/home/shidono/Desktop/godsake/pics/bigsi.png");
    yaru = lock.image;

    lockpick.pos.x = 250;
    lockpick.pos.y = 50;

    lock.pos.x = 355;
    lock.pos.y = 160;


    int done=1,x=0,y=0,angle[3],var = 0,new=0,compteur = 0;

    angle[0] = 0;
    angle[1] = 20;
    angle[2] = -20;
    rec = lock.pos;
    //yaru = rotozoomSurface(lock.image,angle,1.2,1);
   while(done){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    SDL_Quit();
                break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    if(hover(rec,x,y) & SDL_BUTTON(SDL_BUTTON_LEFT)){
                        while(new == var){
                            srand(time(0));
                            var=(rand() % (2-0+1))+0;
                            printf("new : %d\n",new);
                            printf("var : %d\n",var);

                        }
                        new = var;
                        if(new != 0){
                            rec.x = 330;
                            rec.y = 140;
                        }else{
                            rec.x = 355;
                            rec.y = 160;
                        }
                        compteur++;
                        if(compteur == 5){
                            yaru = rotozoomSurface(lock.image,0,1.2,1);
                            rotateimage=rotozoomSurface(yaru,angle[new],1.0,0);
                            SDL_FillRect(screen,NULL,0);
                            SDL_BlitSurface(lockpick.image,NULL,screen,&lockpick.pos);
                            SDL_BlitSurface(rotateimage,NULL,screen,&rec);
                            SDL_Flip(screen);
                            SDL_Delay(1000);
                            done = 0;
                        }
                        //printf("%d \n",angle);
                    }
                break;
            }
        }
        rotateimage=rotozoomSurface(lock.image,angle[new],1.0,0);
        //SDL_SetColorKey(rotateimage,SDL_SRCCOLORKEY,SDL_MapRGB(rotateimage->format,255,0,255));
        //rec.x-=rotateimage->w/2-lock.image->w/2;
        //rec.y-=rotateimage->h/2-lock.image->h/2;
        SDL_FillRect(screen,NULL,0);
        SDL_BlitSurface(lockpick.image,NULL,screen,&lockpick.pos);
        SDL_BlitSurface(rotateimage,NULL,screen,&rec);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(lockpick.image);
}