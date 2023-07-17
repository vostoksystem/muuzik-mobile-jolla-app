/**
  * @brief formate une durée numerique en chîne lisible
  */
var getDuree = function (d) {
    try {
        var o=d;
        var h = (Math.floor(d/3600.0)).toFixed();
        d %= 3600;
        var m = (Math.floor(d/60.0)).toFixed();
        var s = d%60;

        var f= (h>0 ? h + ":":"") +
                (m <10? "0" : "")+ m + ":"+
                (s<10? "0" : "")+ s;
        return h>0 || m>0 || s>0 ? f : "";
    }catch(e) {
    }
    return "";
}


/**
  *retourne la taille en format "humain"
  *param v : tailel en octet
  *return chaine corespondante : xMb, Gb...
  */
var getTaille=function(v, precision) {
    precision = typeof precision === "undefined" ? 1 : precision;

    if(v > 1073741824) {
        return (v / 1073741824).toFixed(precision) + "Gb";
    }
    if(v > 1048576) {
        return (v / 1048576).toFixed(precision) + "Mb";
    }
    if(v > 1024) {
        return (v / 1024).toFixed(precision) + "Kb";
    }

    return v + "octets";
}


/**
  * @ brief retourne le rep parent de v
  */
var getRepParent=function(v) {
    var a = /(.*)\/[^\/]+$/.exec(v);
    if(a.length<=1) {
        return "unknow";
    }

    return a[1];
}

/**
  * @brief retourne le nom du fichir depuis un path
  */
var getNom=function(v) {
    var a = /([^/]+)$/.exec(v);
    if(a) {
        if(a.length<=1) {
            return "unknow";
        }
        return a[1];
    }

    return v;
}

/**
  * @brief retourne le non simple - sans path ou extension depuis un path
  */
var getNomSimple=function(v) {
    var a = /([^/]*)\\.[^\\.]+/.exec(v);
    if(a) {
        if(a.length<=1) {
            return "/";
        }

        return a[1];
    }

    return getNom(v);
}

/**
  *
  */
var getRandomInt=function(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min)) + min;
}


/**
  *
  */
var fastChecksum=function(s) {
    try {
        var r = 0;
        for (var index = 0; index < s.length; ++index) {
            r += s.charCodeAt(index)+index;
        }
        return r;
    }catch(e) {}
    return 0;
}

/**
  *
  */
var ouvrir=function (v) {
    pageStack.push(Qt.resolvedUrl("../pages/Navigateur.qml"), {adresse:v})
}

/**
  *
  */
var ecouter=function (v) {
    lecteurService.remplacer([v]);
    pageStack.push(Qt.resolvedUrl("../pages/ListeLecture.qml"));
}

/**
  *
  */
var ajouter=function (v) {
    lecteurService.ajouter([v]);
}





