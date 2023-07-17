/** formate une durée en hh:mm:ss
  *param: d en seconde
  *return : chaîne hh::mm::ss
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

/** date du jour, premiere seconde
  *param d : timestamp ou current si aucun
  *return : timestamp
  */
var debutduJour = function(d) {
    d = typeof d === "undefined" ? new Date().getTime() : d;
    d = d  - (d % 86400000);
    return d;
}

/** date du jour, dernière seconde
  *param d : timestamp ou current si aucun
  *return : timestamp
  */
var finDuJour = function(d) {
    return debutduJour(d) + 86399000;
}
