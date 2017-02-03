drop table if exists user_dimension;
drop table if exists place_dimension;
drop table if exists time_dimension;
drop table if exists date_dimension;
drop table if exists reserves;

create table user_dimension
  (nif numeric(15,0) not null,
  nome varchar(255) not null,
  telefone numeric(9,0) not null,
  primary key(nif),
  foreign key(nif) references user(nif) ON DELETE CASCADE);

create table place_dimension
  (place_dim_id char(255) not null unique,
  morada varchar(255) not null,
  codigo_posto varchar(255),
  codigo_espaco varchar(255) not null,
  primary key(place_dim_id),
  foreign key(morada, codigo_espaco) references espaco(morada, codigo) ON DELETE CASCADE,
  foreign key(morada, codigo_posto) references posto(morada, codigo) ON DELETE CASCADE);

create table time_dimension
  (time_dim_id int not null unique,
  time_hour int not null,
  time_minutes int not null,
  time_total_minutes int not null,
  primary key(time_dim_id));

create table date_dimension
  (date_dim_id date not null unique,
  date_day int not null,
  date_week int not null,
  date_month int not null,
  date_semester int not null,
  date_year int not null,
  primary key(date_dim_id));

  create table reserves
    (reserves_id varchar(255) not null unique,
    user_dim_id numeric(15,0) not null,
    place_dim_id char(255) not null,
    time_dim_id int not null,
    date_dim_id date not null,
    payed_sum numeric(15,2) not null,
    duration_time int not null,
    primary key(reserves_id),
    foreign key(user_dim_id) references user_dimension(nif) ON DELETE CASCADE,
    foreign key(place_dim_id) references place_dimension(place_dim_id) ON DELETE CASCADE,
    foreign key(time_dim_id) references time_dimension(time_dim_id) ON DELETE CASCADE,
    foreign key(date_dim_id) references date_dimension(date_dim_id) ON DELETE CASCADE);
