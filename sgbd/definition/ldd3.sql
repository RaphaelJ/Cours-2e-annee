BEGIN;

CREATE INDEX I_CLIENTS_CODEPAYS ON CLIENTS.CODEPAYS;
CREATE INDEX I_VILLAGES_CODEPAYS ON VILLAGES.CODEPAYS;
CREATE INDEX I_SEJOURS_IDCLIENT ON SEJOURS.ID_CLIENTS;
CREATE INDEX I_SEJOURS_

COMMIT;