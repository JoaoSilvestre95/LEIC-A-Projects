drop table if exists user_dimension;
drop table if exists place_dimension;
drop table if exists time_dimension;
drop table if exists date_dimension;
drop table if exists reserves;
drop table if exists estado;
drop table if exists paga;
drop table if exists aluga;
drop table if exists reserva;
drop table if exists oferta;
drop table if exists posto;
drop table if exists espaco;
drop table if exists fiscaliza;
drop table if exists arrenda;
drop table if exists alugavel;
drop table if exists edificio;
drop table if exists fiscal;
drop table if exists user;


create table user
  (nif numeric(15,0) not null unique,
   nome varchar(255) not null,
   telefone numeric(9,0) not null,
   primary key(nif));

create table reserva
 (numero varchar(255) not null unique,
  primary key(numero));

create table fiscal
 (id numeric(15,0) not null unique,
  empresa varchar(255) not null,
  primary key(id));

create table edificio
  (morada varchar(255) not null unique,
   primary key(morada));

create table alugavel
 (morada varchar(255) not null,
  codigo varchar(255) not null,
  foto varchar(255) not null,
  primary key(morada, codigo),
  foreign key(morada) references edificio(morada) ON DELETE CASCADE);

create table arrenda
  (morada varchar(255) not null,
   codigo varchar(255) not null,
   nif numeric(15,0) not null,
   primary key(morada, codigo),
   foreign key(morada, codigo) references alugavel(morada, codigo) ON DELETE CASCADE,
   foreign key(nif) references user(nif) ON DELETE CASCADE);

create table fiscaliza
  (id numeric(15,0) not null,
   morada varchar(255) not null,
   codigo varchar(255) not null,
   primary key(id, morada, codigo),
   foreign key(id) references fiscal(id) ON DELETE CASCADE,
   foreign key(morada, codigo) references arrenda(morada, codigo) ON DELETE CASCADE);

create table espaco
  (morada varchar(255) not null,
   codigo varchar(255) not null,
   primary key(morada, codigo),
   foreign key(morada, codigo) references alugavel(morada, codigo) ON DELETE CASCADE);

create table posto
  (morada varchar(255) not null,
   codigo varchar(255) not null,
   codigo_espaco varchar(255) not null,
   primary key(morada, codigo),
   foreign key(morada, codigo) references alugavel(morada, codigo) ON DELETE CASCADE,
   foreign key(morada, codigo_espaco) references espaco(morada, codigo) ON DELETE CASCADE);

create table oferta
  (morada varchar(255) not null,
   codigo varchar(255) not null,
   data_inicio date not null,
   data_fim date not null,
   tarifa numeric(10,2) not null,
   primary key(morada, codigo, data_inicio),
   foreign key(morada, codigo) references alugavel(morada, codigo) ON DELETE CASCADE);

create table aluga
  (morada varchar(255) not null,
   codigo varchar(255) not null,
   data_inicio date not null,
   nif numeric(15,0) not null,
   numero varchar(255) not null,
   primary key(morada, codigo, data_inicio, nif, numero),
   foreign key(morada, codigo, data_inicio) references oferta(morada, codigo, data_inicio) ON DELETE CASCADE,
   foreign key(nif) references user(nif) ON DELETE CASCADE,
   foreign key(numero) references reserva(numero) ON DELETE CASCADE);

create table paga
  (numero varchar(255) not null unique,
   data timestamp not null,
   metodo varchar(255) not null,
   primary key(numero),
   foreign key(numero) references reserva(numero) ON DELETE CASCADE);

create table estado
  (numero varchar(255) not null,
  time_stamp timestamp not null,
  estado varchar(255) not null,
  primary key(numero, time_stamp),
  foreign key(numero) references reserva(numero) ON DELETE CASCADE);
