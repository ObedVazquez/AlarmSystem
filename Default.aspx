<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        Sistema de Alarma </div>
    <p>
        <asp:ScriptManager ID="ScriptManager1" runat="server">
        </asp:ScriptManager>
    </p>
    <p>
        <strong>Alarma 1</strong></p>
    <asp:UpdatePanel ID="UpdatePanel1" runat="server">
        <ContentTemplate>
            <p>
                Activación remota:
                <asp:Label ID="lblEstado" runat="server" Text="Sin Estado"></asp:Label>
            </p>
            <p>
                Activar:
                <asp:CheckBox ID="chkActivar" runat="server" 
        oncheckedchanged="chkActivar_CheckedChanged" />
                <asp:Label ID="lblStatusActivar" runat="server"></asp:Label>
            </p>
            <p>
                <asp:Timer ID="Timer1" runat="server" Interval="1000" ontick="Timer1_Tick">
                </asp:Timer>
            </p>
        </ContentTemplate>
    </asp:UpdatePanel>
    </form>
</body>
</html>
