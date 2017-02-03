/*Queries*/

/*a)*/

select distinct morada, codigo_espaco
from posto
where (morada, codigo, codigo_espaco) not in (
  select morada, codigo, codigo_espaco
  from aluga natural join estado natural join posto
  where estado = "Aceite"
);

/*b)*/
select morada
from aluga
group by morada
having count(*) > (
  select avg(reserveCount)
  from (
    select count(*) as reserveCount
    from aluga
    group by morada
  ) as avgReserve
);

/*c)*/

select nif
from fiscaliza natural join arrenda
group by nif
having count(distinct id) = 1;

/*d)*/
select morada, codigo, sum(montante)
from(
  select morada, codigo, montante
  from (
    select morada, codigo as codigo_posto, codigo_espaco as codigo, tarifa*datediff(data_fim,data_inicio) as montante
    from aluga natural join estado natural join oferta natural join posto
    where estado = "Paga" and year(time_stamp) = 2016
  ) postos_pagos
  union
  select morada, codigo, tarifa*datediff(data_fim,data_inicio) as montante
  from aluga natural join estado natural join oferta natural join espaco
  where estado = "Paga" and year(time_stamp) = 2016
) tabela_montantes
group by morada, codigo;

/*e)*/
select morada, codigo_espaco
from(
  (select morada, codigo_espaco, count(*) as count_postos
  from posto
  group by morada, codigo_espaco) as countPostos
  natural join
  (select morada, codigo_espaco, count(*) as count_aceites
  from (
    select *
    from aluga natural join estado
    where estado = "Aceite") as batata natural join posto
  group by morada, codigo_espaco) as countAceites
)
where count_postos = count_aceites;
