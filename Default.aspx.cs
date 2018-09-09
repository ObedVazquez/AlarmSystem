using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Windows.Forms;
using System.ComponentModel;

public partial class _Default : System.Web.UI.Page
{

    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void Timer1_Tick(object sender, EventArgs e)
    {
        lblEstado.Text = WebService.estado1;
        chkActivar.Checked = WebService.activar;
        
    }

    protected void chkActivar_CheckedChanged(object sender, EventArgs e)
    {
        WebService.activar = chkActivar.Checked;
        if (chkActivar.Checked)
        {
            WebService.EnviaRemoto("http://169.254.43.10", "1");
            lblStatusActivar.Text = Convert.ToString("ALARMA EN EDIFICIO 1: ACTIVADA");
        }
        else
        {
            WebService.EnviaRemoto("http://169.254.43.10", "0");
            lblStatusActivar.Text = Convert.ToString(" ");
        }
    }

}