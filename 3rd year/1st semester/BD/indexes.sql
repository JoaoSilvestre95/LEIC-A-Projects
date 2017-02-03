

-- a)

CREATE INDEX dadosArrendaIdx ON arrenda(morada, codigo);
CREATE INDEX dadosFiscalizaIdx ON fiscaliza(morada, codigo);
CREATE INDEX dadosIdIdx ON fiscaliza(id);

-- b)

CREATE INDEX dadosPostoIdx ON posto(morada, codigo_espaco);
CREATE INDEX estadoIdx ON estado(estado);
