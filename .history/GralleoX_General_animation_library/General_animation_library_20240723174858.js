function changeposition(id,top,left,right,bottom){
    element=document.getElementById(id);
    element.animation="change 2s ease-in-out";
    styleelement=document.createElement('style');
    document.head.appendChild(styleelement);
    fromtop=document.gete
    fromleft=document.gete
    fromright=document.gete
    frombottom=document.gete
    keyframes='@keyframes change {\
        0% {\
            top   : 0px;\
            left  : 0px;\
            right : 0px;\
            bottom: 0px;\
        }\
        100% {\
            top   : '+top+';\
            left  : '+left+';\
            right : '+right+';\
            bottom: '+bottom+';\
        }\
    }';

}