<html>
    <body>
        <h3>Pagar Reserva</h3>
        <form action="pay_Reserva_script.php" method="post">
            <p><input type="hidden"></p>
            <p>Qual a reserva que quer pagar?<p>
            <p>Numero reserva: <input type="text" name="numero"/></p>
            <p>Data: <input type="text" name="data"/></p>
            <p>Metodo de Pagamento: <input type="text" name="metodo"/></p>
            <p><input type="submit" value="Submit"/></p>
        </form>
        <form action="../index.html">
          <input type="submit" value="Voltar" />
        </form>
    </body>
</html>
