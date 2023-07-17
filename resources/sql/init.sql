CREATE TABLE IF NOT EXISTS Item
(
ID INTEGER PRIMARY KEY AUTOINCREMENT,

    -- nom du fichier ou du repertoire, formaté pour l'afficharge (pas d'extention de _ etc...)
    nom TEXT not NULL,
    -- chemin (virtuel) vers le fichier ou repertoire
    chemin TEXT UNIQUE,
    -- liste de mot clee
    motscles TEXT,
    -- format 0 pour rep, 1 pour audio
    format INTEGER
    );

CREATE TABLE IF NOT EXISTS Historique
(
ID INTEGER PRIMARY KEY AUTOINCREMENT,

    -- nom du du repertoire / album
    nom TEXT,
    -- chemin (virtuel) vers le repertoire
    chemin TEXT UNIQUE,
    -- date de derniere ouverture en minute depuis epoch
    ouverture INTEGER,
    -- nombre de fois ou le rep a été ouvert
    nombre INTEGER,
    -- taille en seconde de l'album
    duree INTEGER,
    -- nombre de pistes de l'album
    pistes INTEGER
  );

CREATE TABLE IF NOT EXISTS Favoris
(
ID INTEGER PRIMARY KEY AUTOINCREMENT,

    -- nom du du repertoire / album
    nom TEXT,
    -- chemin (virtuel) vers le repertoire
    chemin TEXT UNIQUE,
    -- date de creation en minute depuis epoch
    creation INTEGER,
    -- taille en seconde de l'album
    duree INTEGER,
    -- nombre de pistes de l'album
    pistes INTEGER
  );

