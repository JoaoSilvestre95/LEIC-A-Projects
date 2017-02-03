<html>
    <body>
<?php

    $morada = $_REQUEST['morada'];
    $codigo = $_REQUEST['codigo'];
    $dataI = $_REQUEST['dataI'];

    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180996";
        $password = "banana";
        $dbname = $user;
        $db = new PDO("mysql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $db->query("start transaction;");


        $sql = "DELETE FROM oferta WHERE morada='$morada' and codigo='$codigo' and data_inicio='$dataI';";

        $db->query($sql);

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
