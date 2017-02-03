drop trigger if exists dataSobreposta;
drop trigger if exists dataPagamentoInvalido;
drop procedure if exists load_user_dim;
drop procedure if exists load_place_dim;
drop procedure if exists load_time_dim;
drop procedure if exists load_date_dim;
drop procedure if exists load_reserves;
drop procedure if exists OLAP_search;


delimiter //
create trigger dataSobreposta before insert on oferta
for each row
begin
  if exists (select * from oferta
    where (morada = new.morada and codigo = new.codigo and (new.data_inicio < data_fim and new.data_fim > data_inicio)))
  then
    call my_capacity_to_insert_this_Offer;
  end if;
end; //
delimiter ;

delimiter //
create trigger dataPagamentoInvalido before insert on paga
for each row
begin
  if new.data <= (select max(time_stamp) from estado where numero=new.numero)
  then
    call my_capacity_to_pay_this;
  end if;
end; //
delimiter ;

delimiter //
CREATE PROCEDURE load_user_dim()
BEGIN
   INSERT INTO user_dimension(nif, nome, telefone)
        select nif, nome, telefone from user;
END; //

delimiter //
CREATE PROCEDURE load_place_dim()
BEGIN
   INSERT INTO place_dimension(place_dim_id, morada, codigo_espaco, codigo_posto)
   select concat(morada, codigo), morada, codigo_espaco, codigo from posto
   union
   select concat(morada, codigo), morada, codigo, null from espaco;
END; //

delimiter //
CREATE PROCEDURE load_time_dim()
BEGIN
   DECLARE v_full_date TIME;
   SET v_full_date = '00:00:00';
   WHILE v_full_date < '24:00:00' DO
       INSERT INTO time_dimension(time_dim_id, time_hour, time_minutes, time_total_minutes)
       VALUES (HOUR(v_full_date) * 100 + MINUTE(v_full_date),
           HOUR(v_full_date),
           MINUTE(v_full_date),
           HOUR(v_full_date)*60 + MINUTE(v_full_date));
       SET v_full_date = ADDTIME(v_full_date, '00:01:00');
   END WHILE;
END;
//

delimiter //
CREATE PROCEDURE load_date_dim()
BEGIN
   DECLARE v_full_date DATE;
   DECLARE semester int;
   SET v_full_date = '2016-01-01';
   WHILE v_full_date < '2018-01-01' DO
        IF MONTH(v_full_date) > 6 THEN SET semester = 2;
        ELSE SET semester = 1;
        END IF;
       INSERT INTO date_dimension(
        date_dim_id,
        date_day,
        date_week,
        date_month,
        date_semester,
        date_year
       ) VALUES (
          v_full_date,
           DAY(v_full_date),
           WEEKOFYEAR(v_full_date),
           MONTH(v_full_date),
           semester,
           YEAR(v_full_date)
       );
       SET v_full_date = DATE_ADD(v_full_date, INTERVAL 1 DAY);
   END WHILE;
END;
//


delimiter //
CREATE PROCEDURE load_reserves()
BEGIN
   INSERT INTO reserves(
     reserves_id,
     user_dim_id,
     place_dim_id,
     time_dim_id,
     date_dim_id,
     payed_sum,
     duration_time)
   select numero, nif, concat(morada, codigo), HOUR(data)*100 + MINUTE(data), date_format(data, '%Y-%m-%d'), tarifa*datediff(data_fim,data_inicio), datediff(data_fim,data_inicio)
   from paga natural join oferta natural join aluga;
END; //


delimiter //
CREATE PROCEDURE OLAP_search()
BEGIN
    select codigo_espaco, codigo_posto, date_day, date_month, avg(payed_sum)
    from reserves natural join place_dimension natural join date_dimension
    group by codigo_espaco, codigo_posto, date_day, date_month with rollup
    union
    select codigo_espaco, codigo_posto, date_day, date_month, avg(payed_sum)
    from reserves natural join place_dimension natural join date_dimension
    group by codigo_posto, date_day, date_month, codigo_espaco with rollup
    union
    select codigo_espaco, codigo_posto, date_day, date_month, avg(payed_sum)
    from reserves natural join place_dimension natural join date_dimension
    group by date_day, date_month, codigo_espaco, codigo_posto with rollup
    union
    select codigo_espaco, codigo_posto, date_day, date_month, avg(payed_sum)
    from reserves natural join place_dimension natural join date_dimension
    group by date_month, codigo_espaco, codigo_posto, date_day with rollup
    union
    select codigo_espaco, codigo_posto, date_day, date_month, avg(payed_sum)
    from reserves natural join place_dimension natural join date_dimension
    group by date_month, codigo_posto, codigo_espaco, date_day with rollup
    union
    select codigo_espaco, codigo_posto, date_day, date_month, avg(payed_sum)
    from reserves natural join place_dimension natural join date_dimension
    group by codigo_espaco, date_day, date_month, codigo_posto with rollup;
END; //
