<html>
    <body>
<?php
    $morada = $_REQUEST['morada'];
    try
    {
    	$host = "db.ist.utl.pt";
        $user ="ist180996";
        $password = "banana";
        $dbname = $user;

        $db = new PDO("mysql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $sql = "select morada, codigo, sum(montante) as Total
        from(
          select morada, codigo, montante
          from (
            select morada, codigo as codigo_posto, codigo_espaco as codigo, tarifa*datediff(data_fim,data_inicio) as montante
            from aluga natural join estado natural join oferta natural join posto
            where estado = 'Paga' and morada = '$morada'
          ) postos_pagos
          union
          select morada, codigo, tarifa*datediff(data_fim,data_inicio) as montante
          from aluga natural join estado natural join oferta natural join espaco
          where estado = 'Paga' and morada = '$morada'
        ) tabela_montantes
        group by morada, codigo;";
        $result = $db->query($sql);

        echo("<table border=\"1\">\n");
        echo("<tr><td>morada</td><td>codigo</td><td>Total</td></tr>\n");
        foreach($result as $row)
        {
            echo("<tr><td>");
            echo($row['morada']);
            echo("</td><td>");
            echo($row['codigo']);
            echo("</td><td>");
            echo($row['Total']);
            echo("</td></tr>\n");
        }
        echo("</table>\n");

        $db = null;
    }
    catch (PDOException $e)
    {
      echo("<p>Ocorreu um erro na base de dados com o codigo: {$e->getMessage()}</p>");
    }
?>
      <form action="../index.html">
        <input type="submit" value="Voltar" />
      </form>
    </body>
</html>
