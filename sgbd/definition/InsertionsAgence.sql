INSERT INTO pays VALUES ('FR', 'France', 'Euro');
INSERT INTO pays VALUES ('B', 'Belgique', 'Euro');
INSERT INTO pays VALUES ('ITL', 'Italie', 'Euro');
INSERT INTO pays VALUES ('P', 'Portugal', 'Euro');
INSERT INTO pays VALUES ('CUB', 'Cuba', 'Peso Cubain');

INSERT INTO villages VALUES('La palmyre', 208, 'FR', 490, 1150, 3);
INSERT INTO villages VALUES('Cervina', 208, 'ITL', 770, 1475, 4);

INSERT INTO stages VALUES('La palmyre', 'Stage Zen', 'Initiation', 70);
INSERT INTO stages VALUES('La palmyre', 'Roller in line', 'Initiation', 0);
INSERT INTO stages VALUES('La palmyre', 'Equitation', 'Tous niveaux', 215);
INSERT INTO stages VALUES('La palmyre', 'Golf', 'Tous niveaux', 340);

INSERT INTO clients VALUES(1, 'Javaux', 'Raphael', 'Angleur', 'ITL', 0);
INSERT INTO clients VALUES(2, 'Javaux', 'Maxime', 'Angleur', 'B', 0);

INSERT INTO sejours VALUES(1, 'La palmyre', TO_DATE('2010-06-30', 'YYYY-MM-DD'), TO_DATE('2010-07-10', 'YYYY-MM-DD'), 10);
INSERT INTO sejours VALUES(2, 'La palmyre', TO_DATE('2010-07-30', 'YYYY-MM-DD'), TO_DATE('2010-08-10', 'YYYY-MM-DD'), 100);
