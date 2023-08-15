using Microsoft.AspNetCore.Mvc;

namespace GameStore.Controllers
{
    public class ItemsController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
