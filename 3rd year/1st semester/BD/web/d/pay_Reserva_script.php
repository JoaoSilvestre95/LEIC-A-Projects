<html>
    <body>
<?php

    $numero = $_REQUEST['numero'];
    $metodo = $_REQUEST['metodo'];
    $data = $_REQUEST['data'];

    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180996";
        $password = "banana";
        $dbname = $user;
        $db = new PDO("mysql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $db->query("start transaction;");


        $sql1 = "INSERT INTO paga VALUES('$numero', '$data', '$metodo');";
        $sql2 = "INSERT INTO estado VALUES('$numero','$data', 'Paga');";

        $db->query($sql1);
        $db->query($sql2);

        $db->query("commit;");

        echo("<p>Sucesso!</p>");

        $db = null;
    }
    catch (PDOException $e)
    {
        $db->query("rollback;");
        echo("<p>Ocorreu um erro na base de dados com o codigo: {$e->getMessage()}</p>");
    }
?>
      <form action="../index.html">
        <input type="submit" value="Voltar" />
      </form>
    </body>
</html>
