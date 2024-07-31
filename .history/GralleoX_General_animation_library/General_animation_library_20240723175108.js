function changeposition(id,top,left,right,bottom){
    element=document.getElementById(id);
    styleelement=document.createElement('style');
    document.head.appendChild(styleelement);
    fromtop=element.top;
    fromleft=element.left;
    fromright=element.right;
    frombottom=element.bottom;
    keyframes='@keyframes change {\
        0% {\
        top   : '+fromtop+';\
        left  : '+fromleft+';\
        right : '+fromright+';\
                bottom: '+frombottom+';\
            }\
            100% {\
            top   : '+top+';\
            left  : '+left+';\
            right : '+right+';\
            bottom: '+bottom+';\
        }\
    }';
    styleelement=keyframes;
    element.animation="change 2s ease-in-out";
    element

}