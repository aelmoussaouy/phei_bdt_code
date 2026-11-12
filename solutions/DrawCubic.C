void DrawCubic() {
   TCanvas *c = new TCanvas("c", "Cubic", 800, 600);

   TF1 *g = new TF1("g", "x*x*x - 3*x*x - 24*x + 5", -7, 7);

   g->SetLineColor(kGreen+2);
   g->SetLineStyle(1);
   g->SetLineWidth(3);

   g->SetTitle("Cubic g(x) = x^{3} - 3x^{2} - 24x + 5;x;g(x)");

   g->Draw();

   c->SaveAs("cubic.png");
   c->SaveAs("cubic.pdf");

   printf("max at x = %g (g = %g), min at x = %g (g = %g)\n",
          g->GetMaximumX(-7, 0), g->GetMaximum(-7, 0),
          g->GetMinimumX(0, 7), g->GetMinimum(0, 7));
}
